/** Delete all triggers **/
DROP TRIGGER IF EXISTS update_cache_characters_insert;
DROP TRIGGER IF EXISTS update_cache_quests_update;
DROP TRIGGER IF EXISTS update_cache_quests_characters_insert;
DROP TRIGGER IF EXISTS update_cache_quests_characters_update;
DROP TRIGGER IF EXISTS update_cache_quests_characters_delete;
DROP TRIGGER IF EXISTS update_cache_charactergroups_insert;
DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_update;
DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_groups_insert;
DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_groups_update;
DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_groups_delete;
DROP TRIGGER IF EXISTS update_cache_characters_charactergroups_insert;
DROP TRIGGER IF EXISTS update_cache_characters_charactergroups_update;
DROP TRIGGER IF EXISTS update_cache_characters_charactergroups_delete;
DROP TRIGGER IF EXISTS update_cache_cache_charactergroups_insert;
DROP TRIGGER IF EXISTS update_cache_cache_charactergroups_update;


/** Delete all routines **/
DROP PROCEDURE IF EXISTS update_cache_characters_quest;
DROP PROCEDURE IF EXISTS update_cache_characters_charactergroup;
DROP PROCEDURE IF EXISTS update_cache_characters;
DROP PROCEDURE IF EXISTS update_cache_charactergroups_charactergroupsquest;
DROP PROCEDURE IF EXISTS update_cache_charactergroups;
