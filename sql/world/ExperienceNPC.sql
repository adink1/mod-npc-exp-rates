-- --------------------------------------------------------------------------------------
-- Master of Experience
-- --------------------------------------------------------------------------------------

DELETE FROM `creature_template` WHERE (`entry` = 929991);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(929991, 0, 0, 0, 0, 0, 28227, 0, 0, 0, 'AlWant', '|cff00ccffMaster of Experience|r', 'Speak', 0, 70, 80, 0, 35, 1, 1, 1.14286, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 'Experience_set', 0);

DELETE FROM `creature_template_locale` WHERE `entry`=929991;
INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`) VALUES
(929991, 'zhCN', '艾尔·旺特', '不眠不休的经验大师', 18019);

DELETE FROM `npc_text` WHERE `id`=929991;
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES (929991, 'Hey there, $N. How can I help you?');

DELETE FROM `npc_text_locale` WHERE `id`=929991;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `Text0_0`) VALUES (929991, 'zhCN', '嘿, $N。需要我帮忙吗?$B$B我可以在你10级之前为你更改升级经验倍率，并且在你满级时，根据你选择的经验倍率为你提供丰厚的奖励');

DELETE FROM `npc_text` WHERE `id`=829992;
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES (829992, 'Hey there, $N. How can I help you?');

DELETE FROM `npc_text_locale` WHERE `id`=829992;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `Text0_0`) VALUES (829992, 'zhCN', '嘿, $N。下面是更改升级经验满级后给予的奖励制度，请仔细阅读，因为你一旦更改，10级之后将不可逆转。$B$B一倍(正常经验)经验额外奖励：$B专家级骑术/寒冷天气飞行/驿站徽章X500$B$B五倍经验奖励：$B专家级骑术/驿站徽章X500$B$B十倍验奖励：$B高级骑术/驿站徽章X300$B$B十五倍经验奖励：$B驿站徽章X200$B$B注意：使用满级令牌将没有任何额外奖励！');

DELETE FROM `creature` WHERE `id1` = 929991;
INSERT INTO `creature` (`guid`, `id1`, `id2`, `id3`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(3110429, 929991, 0, 0, 1, 0, 0, 1, 1, 0, -611.118, -4249.43, 38.9562, 3.34802, 300, 0, 0, 4050, 0, 0, 0, 0, 0, '', 0),
(3110430, 929991, 0, 0, 1, 0, 0, 1, 1, 0, -2915.33, -261.332, 53.2935, 2.4426, 300, 0, 0, 4163, 0, 0, 0, 0, 0, '', 0),
(3110432, 929991, 0, 0, 0, 0, 0, 1, 1, 0, 1838.14, 1628.19, 96.934, 6.20028, 300, 0, 0, 4050, 0, 0, 0, 0, 0, '', 0),
(3110433, 929991, 0, 0, 530, 0, 0, 1, 1, 0, 10340.2, -6362.03, 33.3864, 0.853001, 300, 0, 0, 4163, 0, 0, 0, 0, 0, '', 0),
(3110434, 929991, 0, 0, 530, 0, 0, 1, 1, 0, -4042.47, -13784.5, 75.3376, 6.15987, 300, 0, 0, 5052, 0, 0, 0, 0, 0, '', 0),
(3110436, 929991, 0, 0, 1, 0, 0, 1, 1, 0, 10325.9, 821.992, 1326.41, 2.41129, 300, 0, 0, 4278, 0, 0, 0, 0, 0, '', 0),
(3110437, 929991, 0, 0, 0, 0, 0, 1, 1, 0, -6213.85, 327.614, 383.628, 2.62989, 300, 0, 0, 5052, 0, 0, 0, 0, 0, '', 0),
(3110438, 929991, 0, 0, 0, 0, 0, 1, 1, 0, -8932.94, -130.905, 82.8951, 0.428032, 300, 0, 0, 4916, 0, 0, 0, 0, 0, '', 0);