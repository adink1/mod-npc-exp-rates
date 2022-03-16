/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Config.h"
#include "Object.h"
#include "DataMap.h"
#include "Chat.h"


enum GossipId
{
    Experience_GOSSIP_TEXT        = 48,
    Experience_GOSSIP_AWARD       = 829992,
    Experience_GOSSIP_CHOOSE      = 929991,
    Experience_GOSSIP_CHECK       = 300,
};

bool ExperienceEnable;
bool ExperienceAnnounce;
uint32 DefaultRate;

uint32 item11, mete11, item12, mete12, item13, mete13, item14, mete14, item51, mete51, item52, mete52, item53, mete53, item101, mete101, item102, mete102, item151, mete151, spell1, spell2;

// Add player scripts
class PlayerXpRate : public DataMap::Base
{
public:
    PlayerXpRate() {}
    PlayerXpRate(uint32 XPRate) : XPRate(XPRate) {}
    uint32 XPRate = 1;
};

class Experience_Announce : public PlayerScript
{
public:
    Experience_Announce() : PlayerScript("Experience_Announce") { }
    void OnLogin(Player* player) override
   {
       // Announce Module
       if (ExperienceEnable)
       {
           if (ExperienceAnnounce)
           {
               ChatHandler(player->GetSession()).SendSysMessage("此服务器正在运行|cff4CFF00自主经验选择|r模块。");
            }
        }
    }
};


class Experience_xp : public PlayerScript
{
public:
    Experience_xp() : PlayerScript("Experience_xp") { }
    
    void OnLogin(Player* player) override
    {
        QueryResult result = CharacterDatabase.Query("SELECT `mod_exp` FROM `characters_exp_rates` WHERE `guid` = {}", player->GetGUID().GetCounter());
        if (!result)
        {
            player->CustomData.GetDefault<PlayerXpRate>("Experience_xp")->XPRate = DefaultRate;
        }
        else
        {
            Field* fields = result->Fetch();
            player->CustomData.Set("Experience_xp", new PlayerXpRate(fields[0].Get<uint32>()));
        }
    }

    void OnLogout(Player* player) override
    {
        if (PlayerXpRate* data = player->CustomData.Get<PlayerXpRate>("Experience_xp"))
        {
            uint32 rate = data->XPRate;
            CharacterDatabase.Query("REPLACE INTO characters_exp_rates (`guid`, `mod_exp`) VALUES ({}, {});", player->GetGUID().GetCounter(),rate);
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/) override
    {
        if (ExperienceEnable)
        {
            if (PlayerXpRate* data = player->CustomData.Get<PlayerXpRate>("Experience_xp"))
            {
                amount *= data->XPRate;
            }
        }
    }
};

class Experience_award : public PlayerScript
{
public:
    Experience_award() : PlayerScript("Experience_award") { }
    
    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        if (PlayerXpRate* data = player->CustomData.Get<PlayerXpRate>("Experience_xp"))
        {
            uint32 rate = data->XPRate;
            if (oldLevel < 60 && player->getLevel() == 60)
            {
                if (rate < 11)
                {
                    player->learnSpell(spell1);
                }
            }
            else if (oldLevel < 70 && player->getLevel() == 70)
            {
                if (rate == 1)
                {
                    player->AddItem(item11, mete11);
                    player->AddItem(item12, mete12);
                    player->AddItem(item13, mete13);
                    player->AddItem(item14, mete14);
                    player->learnSpell(spell2);
                }
                else if (rate == 5)
                {
                    player->AddItem(item51, mete51);
                    player->AddItem(item52, mete52);
                    player->AddItem(item53, mete53);
                    player->learnSpell(spell2);
                }
                else if (rate == 10)
                {
                    player->AddItem(item101, mete101);
                    player->AddItem(item102, mete102);
                }
                else if (rate == 15)
                {
                    player->AddItem(item151, mete151);
                }
            }
        }
    }
};

class Experience_set : public CreatureScript
{
public:
    Experience_set() : CreatureScript("Experience_set") { }
    
       bool OnGossipHello(Player* player, Creature* creature) override
        {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "我想选择经验倍率", GOSSIP_SENDER_MAIN, Experience_GOSSIP_CHOOSE);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "我想查看当前经验倍率", GOSSIP_SENDER_MAIN, Experience_GOSSIP_CHECK);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "我想知道奖励制度", GOSSIP_SENDER_MAIN, Experience_GOSSIP_AWARD);
            SendGossipMenuFor(player, Experience_GOSSIP_TEXT, creature->GetGUID());
            return true;
        }
       
       bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();
            
            if (sender != GOSSIP_SENDER_MAIN)
                return false;

            if (action == 1)
            {
                OnGossipHello(player, creature);
            }
            else if (action == Experience_GOSSIP_CHOOSE)
            {
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "我想使用正常经验练级(1倍)", GOSSIP_SENDER_MAIN, Experience_GOSSIP_CHOOSE + 1, "一倍经验练级较慢但奖励丰厚，请问你确定了吗？", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "我想使用五倍经验练级(5倍)", GOSSIP_SENDER_MAIN, Experience_GOSSIP_CHOOSE + 2, "五倍经验练级大约需要七天满级，请问你确定了吗？", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "我想使用十倍经验练级(10倍)", GOSSIP_SENDER_MAIN, Experience_GOSSIP_CHOOSE + 3, "十倍经验经验大约需要三天满级，请问你确定了吗？", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "我想使用十五倍经验练级(15倍)", GOSSIP_SENDER_MAIN, Experience_GOSSIP_CHOOSE + 4, "十五倍经验升级很快但奖励很少，请问你确定了吗？", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
                SendGossipMenuFor(player, Experience_GOSSIP_CHOOSE, creature->GetGUID());
            }
            else if (action == Experience_GOSSIP_CHOOSE + 1)
            {
                if (player->getLevel() >= 10)
                {
                    player->GetSession()->SendNotification("抱歉，升级经验只能在 10 级之前可以更改。");
                    CloseGossipMenuFor(player);
                    return false;
                }
                else
                {
                    Player* me = player->GetSession()->GetPlayer();
                    if (!me)
                    return false;
                    uint32 rate = 1;
                    me->CustomData.GetDefault<PlayerXpRate>("Experience_xp")->XPRate = rate;
                    player->GetSession()->SendNotification("恭喜，你的升级经验已成功修改为 %u 倍！", rate);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }
            else if (action == Experience_GOSSIP_CHOOSE + 2)
            {
                if (player->getLevel() >= 10)
                {
                    player->GetSession()->SendNotification("抱歉，升级经验只能在 10 级之前可以更改。");
                    CloseGossipMenuFor(player);
                    return false;
                }
                else
                {
                    Player* me = player->GetSession()->GetPlayer();
                    if (!me)
                    return false;
                    uint32 rate = 5;
                    me->CustomData.GetDefault<PlayerXpRate>("Experience_xp")->XPRate = rate;
                    player->GetSession()->SendNotification("恭喜，你的升级经验已成功修改为 %u 倍！", rate);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }
            else if (action == Experience_GOSSIP_CHOOSE + 3)
            {
                if (player->getLevel() >= 10)
                {
                    player->GetSession()->SendNotification("抱歉，升级经验只能在 10 级之前可以更改。");
                    CloseGossipMenuFor(player);
                    return false;
                }
                else
                {
                    Player* me = player->GetSession()->GetPlayer();
                    if (!me)
                    return false;
                    uint32 rate = 10;
                    me->CustomData.GetDefault<PlayerXpRate>("Experience_xp")->XPRate = rate;
                    player->GetSession()->SendNotification("恭喜，你的升级经验已成功修改为 %u 倍！", rate);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }
            else if (action == Experience_GOSSIP_CHOOSE + 4)
            {
                if (player->getLevel() >= 10)
                {
                    player->GetSession()->SendNotification("抱歉，升级经验只能在 10 级之前可以更改。");
                    CloseGossipMenuFor(player);
                    return false;
                }
                else
                {
                    Player* me = player->GetSession()->GetPlayer();
                    if (!me)
                    return false;
                    uint32 rate = 15;
                    me->CustomData.GetDefault<PlayerXpRate>("Experience_xp")->XPRate = rate;
                    player->GetSession()->SendNotification("恭喜，你的升级经验已成功修改为 %u 倍！", rate);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }
            else if (action == Experience_GOSSIP_AWARD)
            {
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
                SendGossipMenuFor(player, Experience_GOSSIP_AWARD, creature->GetGUID());
            }
            else if (action == Experience_GOSSIP_CHECK)
            {
                if (PlayerXpRate* data = player->CustomData.GetDefault<PlayerXpRate>("Experience_xp"))
                {
                    uint32 rate = data->XPRate;
                    player->GetSession()->SendNotification("你当前升级经验的倍率为：%u 倍！", rate);
                    CloseGossipMenuFor(player);
                }
            }
            return true;
        }
};

class Experience_conf : public WorldScript
{
public:
    Experience_conf() : WorldScript("Experience_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            ExperienceEnable = sConfigMgr->GetOption<bool>("Experience.Enable", true);
            ExperienceAnnounce = sConfigMgr->GetOption<bool>("Experience.Announce", false);
            DefaultRate = sConfigMgr->GetOption<uint32>("Defaultexp", 1);
            // Full level Award
            item11 = sConfigMgr->GetOption<uint32>("Experience.item11", 0);
            mete11 = sConfigMgr->GetOption<uint32>("Experience.mete11", 0);
            item12 = sConfigMgr->GetOption<uint32>("Experience.item12", 0);
            mete12 = sConfigMgr->GetOption<uint32>("Experience.mete12", 0);
            item13 = sConfigMgr->GetOption<uint32>("Experience.item13", 0);
            mete13 = sConfigMgr->GetOption<uint32>("Experience.mete13", 0);
            item14 = sConfigMgr->GetOption<uint32>("Experience.item14", 0);
            mete14 = sConfigMgr->GetOption<uint32>("Experience.mete14", 0);
            item51 = sConfigMgr->GetOption<uint32>("Experience.item51", 0);
            mete51 = sConfigMgr->GetOption<uint32>("Experience.mete51", 0);
            item52 = sConfigMgr->GetOption<uint32>("Experience.item52", 0);
            mete52 = sConfigMgr->GetOption<uint32>("Experience.mete52", 0);
            item53 = sConfigMgr->GetOption<uint32>("Experience.item53", 0);
            mete53 = sConfigMgr->GetOption<uint32>("Experience.mete53", 0);
            item101 = sConfigMgr->GetOption<uint32>("Experience.item101", 0);
            mete101 = sConfigMgr->GetOption<uint32>("Experience.mete101", 0);
            item102 = sConfigMgr->GetOption<uint32>("Experience.item102", 0);
            mete102 = sConfigMgr->GetOption<uint32>("Experience.mete102", 0);
            item151 = sConfigMgr->GetOption<uint32>("Experience.item151", 0);
            mete151 = sConfigMgr->GetOption<uint32>("Experience.mete151", 0);
            spell1 = sConfigMgr->GetOption<uint32>("Experience.spell1", 0);
            spell2 = sConfigMgr->GetOption<uint32>("Experience.spell2", 0);
        }
    }
};

// Add all scripts in one
void AddSC_ExperienceScripts()
{
    new Experience_xp();
    new Experience_set();
    new Experience_award();
    new Experience_conf();
    new Experience_Announce();
};
