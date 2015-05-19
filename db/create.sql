-- MySQL dump 10.15  Distrib 10.0.18-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: z
-- ------------------------------------------------------
-- Server version	10.0.18-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `achievementconditions`
--

DROP TABLE IF EXISTS `achievementconditions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievementconditions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `condition` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievementconditions_achievement`
--

DROP TABLE IF EXISTS `achievementconditions_achievement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievementconditions_achievement` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `achievement_id` int(11) NOT NULL,
  `field` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `count` tinyint(1) NOT NULL DEFAULT '0',
  `value` int(11) NOT NULL,
  `meta_achievement_id` int(11) DEFAULT NULL,
  `groupby` varchar(128) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `achievement_id` (`achievement_id`),
  KEY `meta_achievement_id` (`meta_achievement_id`),
  CONSTRAINT `achievementconditions_achievement_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `achievementconditions_achievement_ibfk_2` FOREIGN KEY (`achievement_id`) REFERENCES `achievements` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `achievementconditions_achievement_ibfk_3` FOREIGN KEY (`meta_achievement_id`) REFERENCES `achievements` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievementconditions_character`
--

DROP TABLE IF EXISTS `achievementconditions_character`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievementconditions_character` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `achievement_id` int(11) NOT NULL,
  `field` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `achievement_id` (`achievement_id`),
  CONSTRAINT `achievementconditions_character_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `achievementconditions_character_ibfk_2` FOREIGN KEY (`achievement_id`) REFERENCES `achievements` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievementconditions_date`
--

DROP TABLE IF EXISTS `achievementconditions_date`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievementconditions_date` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `achievement_id` int(11) NOT NULL,
  `select` varchar(512) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `achievement_id` (`achievement_id`),
  CONSTRAINT `achievementconditions_date_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `achievementconditions_date_ibfk_2` FOREIGN KEY (`achievement_id`) REFERENCES `achievements` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievementconditions_quest`
--

DROP TABLE IF EXISTS `achievementconditions_quest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievementconditions_quest` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `achievement_id` int(11) NOT NULL,
  `field` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `count` tinyint(1) NOT NULL DEFAULT '0',
  `value` int(11) NOT NULL,
  `quest_id` int(11) DEFAULT NULL,
  `status` tinyint(3) unsigned DEFAULT NULL,
  `groupby` varchar(128) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `achievement_id` (`achievement_id`),
  KEY `quest_id` (`quest_id`),
  CONSTRAINT `achievementconditions_quest_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `achievementconditions_quest_ibfk_2` FOREIGN KEY (`achievement_id`) REFERENCES `achievements` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `achievementconditions_quest_ibfk_3` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievements`
--

DROP TABLE IF EXISTS `achievements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievements` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `achievementcondition_id` int(11) NOT NULL,
  `pos` int(10) unsigned NOT NULL DEFAULT '1',
  `title` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `progress` tinyint(1) NOT NULL,
  `hidden` tinyint(1) NOT NULL DEFAULT '0',
  `only_once` tinyint(1) NOT NULL DEFAULT '0',
  `all_conditions` tinyint(1) NOT NULL DEFAULT '1',
  `deadline` datetime DEFAULT NULL,
  `unachieved_achievementsmedia_id` int(11) DEFAULT NULL,
  `achieved_achievementsmedia_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` (`seminary_id`,`url`),
  UNIQUE KEY `pos` (`seminary_id`,`pos`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  KEY `achieved_seminarymedia_id` (`achieved_achievementsmedia_id`),
  KEY `unachieved_seminarymedia_id` (`unachieved_achievementsmedia_id`),
  KEY `achievementcondition_id` (`achievementcondition_id`),
  CONSTRAINT `achievements_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `achievements_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `achievements_ibfk_3` FOREIGN KEY (`unachieved_achievementsmedia_id`) REFERENCES `achievementsmedia` (`seminarymedia_id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `achievements_ibfk_4` FOREIGN KEY (`achieved_achievementsmedia_id`) REFERENCES `achievementsmedia` (`seminarymedia_id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `achievements_ibfk_5` FOREIGN KEY (`achievementcondition_id`) REFERENCES `achievementconditions` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievements_characters`
--

DROP TABLE IF EXISTS `achievements_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievements_characters` (
  `achievement_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`achievement_id`,`character_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `achievements_characters_ibfk_1` FOREIGN KEY (`achievement_id`) REFERENCES `achievements` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `achievements_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `achievementsmedia`
--

DROP TABLE IF EXISTS `achievementsmedia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievementsmedia` (
  `seminarymedia_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`seminarymedia_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `achievementsmedia_ibfk_1` FOREIGN KEY (`seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `achievementsmedia_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `avatarpictures`
--

DROP TABLE IF EXISTS `avatarpictures`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `avatarpictures` (
  `seminarymedia_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`seminarymedia_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `avatarpictures_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `avatarpictures_ibfk_3` FOREIGN KEY (`seminarymedia_id`) REFERENCES `seminarymedia` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `avatars`
--

DROP TABLE IF EXISTS `avatars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `avatars` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `charactertype_id` int(11) NOT NULL,
  `xplevel_id` int(11) NOT NULL,
  `avatarpicture_id` int(11) DEFAULT NULL,
  `small_avatarpicture_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `charactertype_id_2` (`charactertype_id`,`xplevel_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `charactertype_id` (`charactertype_id`),
  KEY `xplevel_id` (`xplevel_id`),
  KEY `avatarpicture_id` (`avatarpicture_id`),
  KEY `small_avatarpicture_id` (`small_avatarpicture_id`),
  CONSTRAINT `avatars_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `avatars_ibfk_2` FOREIGN KEY (`charactertype_id`) REFERENCES `charactertypes` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `avatars_ibfk_3` FOREIGN KEY (`xplevel_id`) REFERENCES `xplevels` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `avatars_ibfk_4` FOREIGN KEY (`avatarpicture_id`) REFERENCES `avatarpictures` (`seminarymedia_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `avatars_ibfk_5` FOREIGN KEY (`small_avatarpicture_id`) REFERENCES `avatarpictures` (`seminarymedia_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cache_charactergroups`
--

DROP TABLE IF EXISTS `cache_charactergroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cache_charactergroups` (
  `charactergroup_id` int(11) NOT NULL,
  `xps` int(10) unsigned NOT NULL,
  PRIMARY KEY (`charactergroup_id`),
  CONSTRAINT `cache_charactergroups_ibfk_1` FOREIGN KEY (`charactergroup_id`) REFERENCES `charactergroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_cache_charactergroups_insert` AFTER INSERT ON `cache_charactergroups` FOR EACH ROW BEGIN
	CALL update_cache_characters_charactergroup(NEW.charactergroup_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_cache_charactergroups_update` AFTER UPDATE ON `cache_charactergroups` FOR EACH ROW BEGIN
	CALL update_cache_characters_charactergroup(NEW.charactergroup_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `cache_characters`
--

DROP TABLE IF EXISTS `cache_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cache_characters` (
  `character_id` int(11) NOT NULL,
  `xps` int(10) unsigned NOT NULL,
  `quest_xps` int(10) unsigned NOT NULL,
  `xplevel_id` int(11) NOT NULL,
  `avatar_id` int(11) NOT NULL,
  PRIMARY KEY (`character_id`),
  KEY `xplevel_id` (`xplevel_id`),
  KEY `avatar_id` (`avatar_id`),
  CONSTRAINT `cache_characters_ibfk_1` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `cache_characters_ibfk_2` FOREIGN KEY (`xplevel_id`) REFERENCES `xplevels` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `cache_characters_ibfk_3` FOREIGN KEY (`avatar_id`) REFERENCES `avatars` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `charactergroups`
--

DROP TABLE IF EXISTS `charactergroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactergroups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `charactergroupsgroup_id` int(11) NOT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `motto` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `charactergroupsmedia_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `charactergroupsgroup_id_2` (`charactergroupsgroup_id`,`name`),
  UNIQUE KEY `charactergroupsgroup_id_3` (`charactergroupsgroup_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `charactergroupsgroup_id` (`charactergroupsgroup_id`),
  KEY `charactergroupsmedia_id` (`charactergroupsmedia_id`),
  CONSTRAINT `charactergroups_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `charactergroups_ibfk_3` FOREIGN KEY (`charactergroupsgroup_id`) REFERENCES `charactergroupsgroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroups_ibfk_4` FOREIGN KEY (`charactergroupsmedia_id`) REFERENCES `charactergroupsmedia` (`seminarymedia_id`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Charaktergruppen';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_charactergroups_insert` AFTER INSERT ON `charactergroups` FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(NEW.id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `charactergroupsgroups`
--

DROP TABLE IF EXISTS `charactergroupsgroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactergroupsgroups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `preferred` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `seminary_id_3` (`seminary_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  KEY `seminary_id_2` (`seminary_id`),
  CONSTRAINT `charactergroupsgroups_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `charactergroupsgroups_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `charactergroupsmedia`
--

DROP TABLE IF EXISTS `charactergroupsmedia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactergroupsmedia` (
  `seminarymedia_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`seminarymedia_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `charactergroupsmedia_ibfk_1` FOREIGN KEY (`seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroupsmedia_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `charactergroupsquests`
--

DROP TABLE IF EXISTS `charactergroupsquests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactergroupsquests` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `charactergroupsgroup_id` int(11) NOT NULL,
  `questgroups_id` int(11) NOT NULL,
  `title` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `xps` int(10) unsigned NOT NULL,
  `rules` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `won_text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `lost_text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `questsmedia_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `charactergroupsgroup_id_2` (`charactergroupsgroup_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `charactergroupsgroup_id` (`charactergroupsgroup_id`),
  KEY `questgroups_id` (`questgroups_id`),
  KEY `questsmedia_id` (`questsmedia_id`),
  CONSTRAINT `charactergroupsquests_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `charactergroupsquests_ibfk_2` FOREIGN KEY (`charactergroupsgroup_id`) REFERENCES `charactergroupsgroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroupsquests_ibfk_3` FOREIGN KEY (`questgroups_id`) REFERENCES `questgroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroupsquests_ibfk_4` FOREIGN KEY (`questsmedia_id`) REFERENCES `questsmedia` (`media_id`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_charactergroupsquests_update` AFTER UPDATE ON `charactergroupsquests` FOR EACH ROW BEGIN
	CALL update_cache_charactergroups_charactergroupsquest(NEW.id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `charactergroupsquests_groups`
--

DROP TABLE IF EXISTS `charactergroupsquests_groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactergroupsquests_groups` (
  `charactergroupsquest_id` int(11) NOT NULL,
  `charactergroup_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `xps_factor` float NOT NULL,
  PRIMARY KEY (`charactergroupsquest_id`,`charactergroup_id`),
  KEY `charactergroup_id` (`charactergroup_id`),
  CONSTRAINT `charactergroupsquests_groups_ibfk_1` FOREIGN KEY (`charactergroupsquest_id`) REFERENCES `charactergroupsquests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroupsquests_groups_ibfk_2` FOREIGN KEY (`charactergroup_id`) REFERENCES `charactergroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_charactergroupsquests_groups_insert` AFTER INSERT ON `charactergroupsquests_groups` FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(NEW.charactergroup_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_charactergroupsquests_groups_update` AFTER UPDATE ON `charactergroupsquests_groups` FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(OLD.charactergroup_id);
	CALL update_cache_charactergroups(NEW.charactergroup_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_charactergroupsquests_groups_delete` AFTER DELETE ON `charactergroupsquests_groups` FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(OLD.charactergroup_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `charactergroupsquests_seminaryuploads`
--

DROP TABLE IF EXISTS `charactergroupsquests_seminaryuploads`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactergroupsquests_seminaryuploads` (
  `seminaryupload_id` int(11) NOT NULL,
  `charactergroupsquest_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`seminaryupload_id`),
  KEY `charactergroupsquest_id` (`charactergroupsquest_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `charactergroupsquests_seminaryuploads_ibfk_1` FOREIGN KEY (`seminaryupload_id`) REFERENCES `seminaryuploads` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroupsquests_seminaryuploads_ibfk_2` FOREIGN KEY (`charactergroupsquest_id`) REFERENCES `charactergroupsquests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `charactergroupsquests_seminaryuploads_ibfk_3` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `characterroles`
--

DROP TABLE IF EXISTS `characterroles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characterroles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `name` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `characters`
--

DROP TABLE IF EXISTS `characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `user_id` int(11) NOT NULL,
  `charactertype_id` int(11) NOT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `charactertype_id` (`charactertype_id`),
  KEY `user_id` (`user_id`),
  CONSTRAINT `characters_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `characters_ibfk_2` FOREIGN KEY (`charactertype_id`) REFERENCES `charactertypes` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Charaktere';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_characters_insert` AFTER INSERT ON `characters` FOR EACH ROW BEGIN
	CALL update_cache_characters(NEW.id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `characters_charactergroups`
--

DROP TABLE IF EXISTS `characters_charactergroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_charactergroups` (
  `character_id` int(11) NOT NULL,
  `charactergroup_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`character_id`,`charactergroup_id`),
  KEY `charactergroup_id` (`charactergroup_id`),
  CONSTRAINT `characters_charactergroups_ibfk_1` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `characters_charactergroups_ibfk_2` FOREIGN KEY (`charactergroup_id`) REFERENCES `charactergroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_characters_charactergroups_insert` AFTER INSERT ON `characters_charactergroups` FOR EACH ROW BEGIN
	CALL update_cache_characters(NEW.character_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_characters_charactergroups_update` AFTER UPDATE ON `characters_charactergroups` FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
	CALL update_cache_characters(NEW.character_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_characters_charactergroups_delete` AFTER DELETE ON `characters_charactergroups` FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `characters_characterroles`
--

DROP TABLE IF EXISTS `characters_characterroles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_characterroles` (
  `character_id` int(11) NOT NULL,
  `characterrole_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`character_id`,`characterrole_id`),
  KEY `userseminaryrole_id` (`characterrole_id`),
  CONSTRAINT `characters_characterroles_ibfk_1` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `characters_characterroles_ibfk_2` FOREIGN KEY (`characterrole_id`) REFERENCES `characterroles` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `characters_seminarycharacterfields`
--

DROP TABLE IF EXISTS `characters_seminarycharacterfields`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_seminarycharacterfields` (
  `character_id` int(11) NOT NULL,
  `seminarycharacterfield_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `value` varchar(256) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`character_id`,`seminarycharacterfield_id`),
  KEY `seminarycharacterfield_id` (`seminarycharacterfield_id`),
  CONSTRAINT `characters_seminarycharacterfields_ibfk_1` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `characters_seminarycharacterfields_ibfk_2` FOREIGN KEY (`seminarycharacterfield_id`) REFERENCES `seminarycharacterfields` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `charactertypes`
--

DROP TABLE IF EXISTS `charactertypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charactertypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `name` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`,`seminary_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `charactertypes_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `charactertypes_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Charaktertypen';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `maps`
--

DROP TABLE IF EXISTS `maps`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `maps` (
  `seminary_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `seminarymedia_id` int(11) NOT NULL,
  `width` int(10) unsigned NOT NULL,
  `height` int(10) unsigned NOT NULL,
  PRIMARY KEY (`seminary_id`),
  KEY `seminarymedia_id` (`seminarymedia_id`),
  CONSTRAINT `maps_ibfk_1` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`),
  CONSTRAINT `maps_ibfk_2` FOREIGN KEY (`seminarymedia_id`) REFERENCES `seminarymedia` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `media`
--

DROP TABLE IF EXISTS `media`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `media` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `mimetype` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `seminary_id_2` (`name`),
  UNIQUE KEY `seminary_id_3` (`url`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `media_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgroups`
--

DROP TABLE IF EXISTS `questgroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgroups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `title` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `questgroupspicture_id` int(11) DEFAULT NULL,
  `achievable_xps` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`seminary_id`,`title`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questgroupspicture_id` (`questgroupspicture_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `questgroups_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questgroups_ibfk_4` FOREIGN KEY (`questgroupspicture_id`) REFERENCES `questgroupspictures` (`media_id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `questgroups_ibfk_5` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Aufgabengruppen';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgroups_characters`
--

DROP TABLE IF EXISTS `questgroups_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgroups_characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questgroup_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `status` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `questgroup_id` (`questgroup_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `questgroups_characters_ibfk_1` FOREIGN KEY (`questgroup_id`) REFERENCES `questgroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questgroups_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgroups_questgroupshierarchy`
--

DROP TABLE IF EXISTS `questgroups_questgroupshierarchy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgroups_questgroupshierarchy` (
  `questgroup_id` int(11) NOT NULL,
  `questgroupshierarchy_id` int(11) NOT NULL,
  `parent_questgroup_id` int(11) DEFAULT NULL,
  `pos` int(10) unsigned NOT NULL,
  PRIMARY KEY (`questgroup_id`),
  UNIQUE KEY `pos` (`parent_questgroup_id`,`pos`),
  KEY `parent_questgoup_id` (`parent_questgroup_id`),
  KEY `questgroupshierarchy_id` (`questgroupshierarchy_id`),
  CONSTRAINT `questgroups_questgroupshierarchy_ibfk_1` FOREIGN KEY (`questgroup_id`) REFERENCES `questgroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questgroups_questgroupshierarchy_ibfk_2` FOREIGN KEY (`questgroupshierarchy_id`) REFERENCES `questgroupshierarchy` (`id`),
  CONSTRAINT `questgroups_questgroupshierarchy_ibfk_3` FOREIGN KEY (`parent_questgroup_id`) REFERENCES `questgroups` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgroups_questtexts`
--

DROP TABLE IF EXISTS `questgroups_questtexts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgroups_questtexts` (
  `questgroup_id` int(11) NOT NULL,
  `questtext_id` int(11) NOT NULL,
  `entry_text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`questgroup_id`,`questtext_id`),
  KEY `questtext_id` (`questtext_id`),
  CONSTRAINT `questgroups_questtexts_ibfk_1` FOREIGN KEY (`questgroup_id`) REFERENCES `questgroups` (`id`),
  CONSTRAINT `questgroups_questtexts_ibfk_2` FOREIGN KEY (`questtext_id`) REFERENCES `questtexts` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgroupshierarchy`
--

DROP TABLE IF EXISTS `questgroupshierarchy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgroupshierarchy` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `parent_questgroupshierarchy_id` int(11) DEFAULT NULL,
  `pos` int(10) unsigned NOT NULL,
  `title_singular` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `title_plural` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `pos` (`parent_questgroupshierarchy_id`,`pos`),
  UNIQUE KEY `url` (`seminary_id`,`parent_questgroupshierarchy_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  KEY `parent_questhierarchy_id` (`parent_questgroupshierarchy_id`),
  CONSTRAINT `questgroupshierarchy_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questgroupshierarchy_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questgroupshierarchy_ibfk_3` FOREIGN KEY (`parent_questgroupshierarchy_id`) REFERENCES `questgroupshierarchy` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Aufgabengruppenhierarchie';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgroupspictures`
--

DROP TABLE IF EXISTS `questgroupspictures`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgroupspictures` (
  `media_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`media_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `questgroupspictures_ibfk_1` FOREIGN KEY (`media_id`) REFERENCES `seminarymedia` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questgroupspictures_ibfk_3` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questgrouptexts`
--

DROP TABLE IF EXISTS `questgrouptexts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questgrouptexts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `questgroup_id` int(11) NOT NULL,
  `pos` int(11) NOT NULL DEFAULT '1',
  `text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `questgroup_id_2` (`questgroup_id`,`pos`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questgroup_id` (`questgroup_id`),
  CONSTRAINT `questgrouptexts_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questgrouptexts_ibfk_2` FOREIGN KEY (`questgroup_id`) REFERENCES `questgroups` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `quests`
--

DROP TABLE IF EXISTS `quests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `quests` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `questgroup_id` int(11) NOT NULL,
  `questtype_id` int(11) NOT NULL,
  `title` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `xps` int(11) unsigned NOT NULL,
  `entry_text` text COLLATE utf8mb4_unicode_ci,
  `wrong_text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `task` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `questsmedia_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `questgroup_id_url` (`questgroup_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questtype_id` (`questtype_id`),
  KEY `questmedia_id` (`questsmedia_id`),
  KEY `questgroup_id` (`questgroup_id`),
  CONSTRAINT `quests_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `quests_ibfk_2` FOREIGN KEY (`questtype_id`) REFERENCES `questtypes` (`id`),
  CONSTRAINT `quests_ibfk_4` FOREIGN KEY (`questgroup_id`) REFERENCES `questgroups` (`id`),
  CONSTRAINT `quests_ibfk_5` FOREIGN KEY (`questsmedia_id`) REFERENCES `questsmedia` (`media_id`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_quests_update` AFTER UPDATE ON `quests` FOR EACH ROW BEGIN
	CALL update_cache_characters_quest(NEW.id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `quests_characters`
--

DROP TABLE IF EXISTS `quests_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `quests_characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `quest_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `status` tinyint(4) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `quest_id` (`quest_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `quests_characters_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `quests_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_quests_characters_insert` AFTER INSERT ON `quests_characters` FOR EACH ROW BEGIN
	CALL update_cache_characters(NEW.character_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_quests_characters_update` AFTER UPDATE ON `quests_characters` FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
	CALL update_cache_characters(NEW.character_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`z`@`%`*/ /*!50003 TRIGGER `update_cache_quests_characters_delete` AFTER DELETE ON `quests_characters` FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `quests_previousquests`
--

DROP TABLE IF EXISTS `quests_previousquests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `quests_previousquests` (
  `quest_id` int(11) NOT NULL,
  `previous_quest_id` int(11) NOT NULL,
  PRIMARY KEY (`quest_id`,`previous_quest_id`),
  KEY `previous_quest_id` (`previous_quest_id`),
  CONSTRAINT `quests_previousquests_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `quests_previousquests_ibfk_2` FOREIGN KEY (`previous_quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Vorherige Aufgaben';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `quests_questsubtopics`
--

DROP TABLE IF EXISTS `quests_questsubtopics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `quests_questsubtopics` (
  `quest_id` int(11) NOT NULL,
  `questsubtopic_id` int(11) NOT NULL,
  PRIMARY KEY (`quest_id`,`questsubtopic_id`),
  KEY `questsubtopic_id` (`questsubtopic_id`),
  CONSTRAINT `quests_questsubtopics_ibfk_3` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `quests_questsubtopics_ibfk_4` FOREIGN KEY (`questsubtopic_id`) REFERENCES `questsubtopics` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questsmedia`
--

DROP TABLE IF EXISTS `questsmedia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questsmedia` (
  `media_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`media_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `questsmedia_ibfk_1` FOREIGN KEY (`media_id`) REFERENCES `seminarymedia` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questsmedia_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questsubtopics`
--

DROP TABLE IF EXISTS `questsubtopics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questsubtopics` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `questtopic_id` int(11) NOT NULL,
  `title` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`title`,`questtopic_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questtopic_id` (`questtopic_id`),
  CONSTRAINT `questsubtopics_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questsubtopics_ibfk_2` FOREIGN KEY (`questtopic_id`) REFERENCES `questtopics` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Aufgabenbereiche';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtexts`
--

DROP TABLE IF EXISTS `questtexts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtexts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `quest_id` int(11) NOT NULL,
  `questtexttype_id` int(11) NOT NULL,
  `pos` int(11) NOT NULL DEFAULT '1',
  `text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `out_text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `abort_text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `questsmedia_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `quest_id_2` (`quest_id`,`questtexttype_id`,`pos`),
  KEY `created_user_id` (`created_user_id`),
  KEY `quest_id` (`quest_id`),
  KEY `questtexttype_id` (`questtexttype_id`),
  KEY `questsmedia_id` (`questsmedia_id`),
  CONSTRAINT `questtexts_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtexts_ibfk_3` FOREIGN KEY (`questtexttype_id`) REFERENCES `questtexttypes` (`id`),
  CONSTRAINT `questtexts_ibfk_4` FOREIGN KEY (`questsmedia_id`) REFERENCES `questsmedia` (`media_id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `questtexts_ibfk_5` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtexttypes`
--

DROP TABLE IF EXISTS `questtexttypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtexttypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `type` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `type` (`type`),
  UNIQUE KEY `url` (`url`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtopics`
--

DROP TABLE IF EXISTS `questtopics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtopics` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `title` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` (`seminary_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `questtopics_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtopics_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Aufgabenbereiche';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes`
--

DROP TABLE IF EXISTS `questtypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `title` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `classname` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`title`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_bossfight`
--

DROP TABLE IF EXISTS `questtypes_bossfight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_bossfight` (
  `quest_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `bossname` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `boss_seminarymedia_id` int(11) NOT NULL,
  `lives_character` smallint(5) unsigned NOT NULL,
  `lives_boss` smallint(5) unsigned NOT NULL,
  PRIMARY KEY (`quest_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `boss_seminarymedia_id` (`boss_seminarymedia_id`),
  CONSTRAINT `questtypes_bossfight_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_bossfight_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_bossfight_ibfk_3` FOREIGN KEY (`boss_seminarymedia_id`) REFERENCES `seminarymedia` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_bossfight_stages`
--

DROP TABLE IF EXISTS `questtypes_bossfight_stages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_bossfight_stages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questtypes_bossfight_quest_id` int(11) NOT NULL,
  `parent_stage_id` int(11) DEFAULT NULL,
  `text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `question` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `livedrain_character` smallint(6) NOT NULL,
  `livedrain_boss` smallint(6) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `parent_stage_id` (`parent_stage_id`),
  KEY `questtypes_bossfight_quest_id` (`questtypes_bossfight_quest_id`),
  CONSTRAINT `questtypes_bossfight_stages_ibfk_1` FOREIGN KEY (`questtypes_bossfight_quest_id`) REFERENCES `questtypes_bossfight` (`quest_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_bossfight_stages_ibfk_2` FOREIGN KEY (`parent_stage_id`) REFERENCES `questtypes_bossfight_stages` (`id`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_bossfight_stages_characters`
--

DROP TABLE IF EXISTS `questtypes_bossfight_stages_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_bossfight_stages_characters` (
  `questtypes_bossfight_stage_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`questtypes_bossfight_stage_id`,`character_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `questtypes_bossfight_stages_characters_ibfk_1` FOREIGN KEY (`questtypes_bossfight_stage_id`) REFERENCES `questtypes_bossfight_stages` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_bossfight_stages_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_choiceinput`
--

DROP TABLE IF EXISTS `questtypes_choiceinput`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_choiceinput` (
  `quest_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`quest_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `questtypes_choiceinput_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_choiceinput_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_choiceinput_choices`
--

DROP TABLE IF EXISTS `questtypes_choiceinput_choices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_choiceinput_choices` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questtypes_choiceinput_list_id` int(11) NOT NULL,
  `pos` int(10) unsigned NOT NULL DEFAULT '1',
  `text` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `questtypes_choiceinput_list_id` (`questtypes_choiceinput_list_id`,`pos`),
  CONSTRAINT `questtypes_choiceinput_choices_ibfk_1` FOREIGN KEY (`questtypes_choiceinput_list_id`) REFERENCES `questtypes_choiceinput_lists` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_choiceinput_lists`
--

DROP TABLE IF EXISTS `questtypes_choiceinput_lists`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_choiceinput_lists` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questtypes_choiceinput_quest_id` int(11) NOT NULL,
  `number` int(10) unsigned NOT NULL,
  `questtypes_choiceinput_choice_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `questtypes_textinput_quest_id` (`questtypes_choiceinput_quest_id`,`number`),
  KEY `questtypes_choiceinput_choice_id` (`questtypes_choiceinput_choice_id`),
  CONSTRAINT `questtypes_choiceinput_lists_ibfk_1` FOREIGN KEY (`questtypes_choiceinput_quest_id`) REFERENCES `questtypes_choiceinput` (`quest_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_choiceinput_lists_ibfk_2` FOREIGN KEY (`questtypes_choiceinput_choice_id`) REFERENCES `questtypes_choiceinput_choices` (`id`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_choiceinput_lists_characters`
--

DROP TABLE IF EXISTS `questtypes_choiceinput_lists_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_choiceinput_lists_characters` (
  `character_id` int(11) NOT NULL,
  `questtypes_choiceinput_list_id` int(11) NOT NULL,
  `questtypes_choiceinput_choice_id` int(11) DEFAULT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`character_id`,`questtypes_choiceinput_list_id`),
  KEY `questtypes_choiceinput_choice_id` (`questtypes_choiceinput_choice_id`),
  KEY `questtypes_choiceinput_list_id` (`questtypes_choiceinput_list_id`),
  CONSTRAINT `questtypes_choiceinput_lists_characters_ibfk_1` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_choiceinput_lists_characters_ibfk_2` FOREIGN KEY (`questtypes_choiceinput_list_id`) REFERENCES `questtypes_choiceinput_lists` (`id`),
  CONSTRAINT `questtypes_choiceinput_lists_characters_ibfk_3` FOREIGN KEY (`questtypes_choiceinput_choice_id`) REFERENCES `questtypes_choiceinput_choices` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_crossword_words`
--

DROP TABLE IF EXISTS `questtypes_crossword_words`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_crossword_words` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `quest_id` int(11) NOT NULL,
  `question` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `word` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `vertical` tinyint(1) NOT NULL,
  `pos_x` int(10) unsigned NOT NULL,
  `pos_y` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `quest_id_2` (`quest_id`,`vertical`,`pos_x`,`pos_y`),
  KEY `quest_id` (`quest_id`),
  CONSTRAINT `questtypes_crossword_words_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_crossword_words_characters`
--

DROP TABLE IF EXISTS `questtypes_crossword_words_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_crossword_words_characters` (
  `questtypes_crossword_word_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `answer` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`questtypes_crossword_word_id`,`character_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `questtypes_crossword_words_characters_ibfk_1` FOREIGN KEY (`questtypes_crossword_word_id`) REFERENCES `questtypes_crossword_words` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_crossword_words_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_dragndrop`
--

DROP TABLE IF EXISTS `questtypes_dragndrop`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_dragndrop` (
  `quest_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `questmedia_id` int(11) NOT NULL,
  `width` int(10) unsigned NOT NULL,
  `height` int(10) unsigned NOT NULL,
  PRIMARY KEY (`quest_id`),
  KEY `questmedia_id` (`questmedia_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `questtypes_dragndrop_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_dragndrop_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_dragndrop_ibfk_3` FOREIGN KEY (`questmedia_id`) REFERENCES `questsmedia` (`media_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_dragndrop_drags`
--

DROP TABLE IF EXISTS `questtypes_dragndrop_drags`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_dragndrop_drags` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `questtypes_dragndrop_id` int(11) NOT NULL,
  `questmedia_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `questtypes_dragndrop_id` (`questtypes_dragndrop_id`),
  KEY `questmedia_id` (`questmedia_id`),
  CONSTRAINT `questtypes_dragndrop_drags_ibfk_1` FOREIGN KEY (`questtypes_dragndrop_id`) REFERENCES `questtypes_dragndrop` (`quest_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_dragndrop_drags_ibfk_2` FOREIGN KEY (`questmedia_id`) REFERENCES `questsmedia` (`media_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_dragndrop_drops`
--

DROP TABLE IF EXISTS `questtypes_dragndrop_drops`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_dragndrop_drops` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questtypes_dragndrop_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `top` int(11) NOT NULL,
  `left` int(11) NOT NULL,
  `width` int(10) unsigned NOT NULL,
  `height` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `questtypes_dragndrop_id` (`questtypes_dragndrop_id`),
  CONSTRAINT `questtypes_dragndrop_drops_ibfk_4` FOREIGN KEY (`questtypes_dragndrop_id`) REFERENCES `questtypes_dragndrop` (`quest_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_dragndrop_drops_characters`
--

DROP TABLE IF EXISTS `questtypes_dragndrop_drops_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_dragndrop_drops_characters` (
  `questtypes_dragndrop_drop_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `questtypes_dragndrop_drag_id` int(11) NOT NULL,
  PRIMARY KEY (`questtypes_dragndrop_drop_id`,`character_id`),
  KEY `questtypes_dragndrop_drag_id` (`questtypes_dragndrop_drag_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `questtypes_dragndrop_drops_characters_ibfk_1` FOREIGN KEY (`questtypes_dragndrop_drop_id`) REFERENCES `questtypes_dragndrop_drops` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_dragndrop_drops_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_dragndrop_drops_characters_ibfk_3` FOREIGN KEY (`questtypes_dragndrop_drag_id`) REFERENCES `questtypes_dragndrop_drags` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_dragndrop_drops_drags`
--

DROP TABLE IF EXISTS `questtypes_dragndrop_drops_drags`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_dragndrop_drops_drags` (
  `questtypes_dragndrop_drop_id` int(11) NOT NULL,
  `questtypes_dragndrop_drag_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  PRIMARY KEY (`questtypes_dragndrop_drop_id`,`questtypes_dragndrop_drag_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questtypes_dragndrop_drag_id` (`questtypes_dragndrop_drag_id`),
  CONSTRAINT `questtypes_dragndrop_drops_drags_ibfk_1` FOREIGN KEY (`questtypes_dragndrop_drop_id`) REFERENCES `questtypes_dragndrop_drops` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_dragndrop_drops_drags_ibfk_3` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_dragndrop_drops_drags_ibfk_4` FOREIGN KEY (`questtypes_dragndrop_drag_id`) REFERENCES `questtypes_dragndrop_drags` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_multiplechoice`
--

DROP TABLE IF EXISTS `questtypes_multiplechoice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_multiplechoice` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `quest_id` int(11) NOT NULL,
  `pos` int(10) unsigned NOT NULL DEFAULT '1',
  `question` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `quest_id_2` (`quest_id`,`pos`),
  KEY `created_user_id` (`created_user_id`),
  KEY `quest_id` (`quest_id`),
  CONSTRAINT `questtypes_multiplechoice_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_multiplechoice_ibfk_2` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_multiplechoice_answers`
--

DROP TABLE IF EXISTS `questtypes_multiplechoice_answers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_multiplechoice_answers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `questtypes_multiplechoice_id` int(11) NOT NULL,
  `pos` int(11) NOT NULL,
  `answer` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `tick` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `questtypes_multiplechoice_id_2` (`questtypes_multiplechoice_id`,`pos`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questtypes_multiplechoice_id` (`questtypes_multiplechoice_id`),
  CONSTRAINT `questtypes_multiplechoice_answers_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_multiplechoice_answers_ibfk_2` FOREIGN KEY (`questtypes_multiplechoice_id`) REFERENCES `questtypes_multiplechoice` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_multiplechoice_characters`
--

DROP TABLE IF EXISTS `questtypes_multiplechoice_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_multiplechoice_characters` (
  `questtypes_multiplechoice_answer_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ticked` tinyint(1) NOT NULL,
  PRIMARY KEY (`questtypes_multiplechoice_answer_id`,`character_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `questtypes_multiplechoice_characters_ibfk_1` FOREIGN KEY (`questtypes_multiplechoice_answer_id`) REFERENCES `questtypes_multiplechoice_answers` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_multiplechoice_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_submit_characters`
--

DROP TABLE IF EXISTS `questtypes_submit_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_submit_characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `quest_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `upload_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `character_id` (`character_id`),
  KEY `upload_id` (`upload_id`),
  KEY `quest_id` (`quest_id`),
  CONSTRAINT `questtypes_submit_characters_ibfk_3` FOREIGN KEY (`upload_id`) REFERENCES `seminaryuploads` (`id`),
  CONSTRAINT `questtypes_submit_characters_ibfk_4` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_submit_characters_ibfk_5` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_submit_characters_comments`
--

DROP TABLE IF EXISTS `questtypes_submit_characters_comments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_submit_characters_comments` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `questtypes_submit_character_id` int(11) NOT NULL,
  `comment` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `questtypes_submit_character_id` (`questtypes_submit_character_id`),
  CONSTRAINT `questtypes_submit_characters_comments_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_submit_characters_comments_ibfk_2` FOREIGN KEY (`questtypes_submit_character_id`) REFERENCES `questtypes_submit_characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_submit_mimetypes`
--

DROP TABLE IF EXISTS `questtypes_submit_mimetypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_submit_mimetypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `mimetype` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  `size` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `mimetype` (`mimetype`,`seminary_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `questtypes_submit_mimetypes_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `questtypes_submit_mimetypes_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_textinput`
--

DROP TABLE IF EXISTS `questtypes_textinput`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_textinput` (
  `quest_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`quest_id`),
  KEY `created_user_id` (`created_user_id`),
  CONSTRAINT `questtypes_textinput_ibfk_1` FOREIGN KEY (`quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_textinput_ibfk_2` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_textinput_fields`
--

DROP TABLE IF EXISTS `questtypes_textinput_fields`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_textinput_fields` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questtypes_textinput_quest_id` int(11) NOT NULL,
  `number` int(10) unsigned NOT NULL,
  `questtypes_textinput_fieldsize_id` int(11) NOT NULL DEFAULT '1',
  `regex` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `questtypes_textinput_quest_id` (`questtypes_textinput_quest_id`,`number`),
  KEY `questtypes_textinput_fieldsize_id` (`questtypes_textinput_fieldsize_id`),
  CONSTRAINT `questtypes_textinput_fields_ibfk_1` FOREIGN KEY (`questtypes_textinput_quest_id`) REFERENCES `quests` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_textinput_fields_ibfk_2` FOREIGN KEY (`questtypes_textinput_fieldsize_id`) REFERENCES `questtypes_textinput_fieldsizes` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_textinput_fields_characters`
--

DROP TABLE IF EXISTS `questtypes_textinput_fields_characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_textinput_fields_characters` (
  `questtypes_textinput_field_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `value` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`questtypes_textinput_field_id`,`character_id`),
  KEY `character_id` (`character_id`),
  CONSTRAINT `questtypes_textinput_fields_characters_ibfk_2` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `questtypes_textinput_fields_characters_ibfk_3` FOREIGN KEY (`questtypes_textinput_field_id`) REFERENCES `questtypes_textinput_fields` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `questtypes_textinput_fieldsizes`
--

DROP TABLE IF EXISTS `questtypes_textinput_fieldsizes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `questtypes_textinput_fieldsizes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `size` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `size` (`size`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `seminaries`
--

DROP TABLE IF EXISTS `seminaries`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seminaries` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `title` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `course` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `seminarymedia_id` int(11) DEFAULT NULL,
  `charactergroups_seminarymedia_id` int(11) DEFAULT NULL,
  `achievements_seminarymedia_id` int(11) DEFAULT NULL,
  `library_seminarymedia_id` int(11) DEFAULT NULL,
  `map_seminarymedia_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`title`),
  UNIQUE KEY `url` (`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `media_id` (`seminarymedia_id`),
  KEY `charactergroups_seminarymedia_id` (`charactergroups_seminarymedia_id`),
  KEY `achievements_seminarymedia_id` (`achievements_seminarymedia_id`),
  KEY `library_seminarymedia_id` (`library_seminarymedia_id`),
  KEY `map_seminarymedia_id` (`map_seminarymedia_id`),
  CONSTRAINT `seminaries_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `seminaries_ibfk_2` FOREIGN KEY (`seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `seminaries_ibfk_3` FOREIGN KEY (`charactergroups_seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `seminaries_ibfk_4` FOREIGN KEY (`achievements_seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `seminaries_ibfk_5` FOREIGN KEY (`library_seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `seminaries_ibfk_6` FOREIGN KEY (`map_seminarymedia_id`) REFERENCES `seminarymedia` (`id`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Lehrveranstaltungen';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `seminarycharacterfields`
--

DROP TABLE IF EXISTS `seminarycharacterfields`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seminarycharacterfields` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `pos` int(10) unsigned NOT NULL,
  `title` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `seminarycharacterfieldtype_id` int(11) NOT NULL,
  `regex` varchar(512) COLLATE utf8mb4_unicode_ci NOT NULL,
  `required` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` (`seminary_id`,`url`),
  UNIQUE KEY `seminary_id_2` (`seminary_id`,`pos`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  KEY `seminarycharacterfieldtype_id` (`seminarycharacterfieldtype_id`),
  CONSTRAINT `seminarycharacterfields_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `seminarycharacterfields_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `seminarycharacterfields_ibfk_3` FOREIGN KEY (`seminarycharacterfieldtype_id`) REFERENCES `seminarycharacterfieldtypes` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `seminarycharacterfieldtypes`
--

DROP TABLE IF EXISTS `seminarycharacterfieldtypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seminarycharacterfieldtypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `title` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `seminarymedia`
--

DROP TABLE IF EXISTS `seminarymedia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seminarymedia` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `mimetype` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `seminary_id_2` (`seminary_id`,`name`),
  UNIQUE KEY `seminary_id_3` (`seminary_id`,`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `seminarymedia_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `seminarymedia_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `seminaryuploads`
--

DROP TABLE IF EXISTS `seminaryuploads`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seminaryuploads` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) DEFAULT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `mimetype` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  `public` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` (`url`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `seminaryuploads_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `seminaryuploads_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `userroles`
--

DROP TABLE IF EXISTS `userroles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userroles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `name` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `username` varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `surname` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `prename` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `mailing` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `url` (`url`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Benutzer';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `users_userroles`
--

DROP TABLE IF EXISTS `users_userroles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users_userroles` (
  `user_id` int(11) NOT NULL,
  `userrole_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`user_id`,`userrole_id`),
  KEY `userrole_id` (`userrole_id`),
  CONSTRAINT `users_userroles_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `users_userroles_ibfk_3` FOREIGN KEY (`userrole_id`) REFERENCES `userroles` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `xplevels`
--

DROP TABLE IF EXISTS `xplevels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `xplevels` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_user_id` int(11) NOT NULL,
  `seminary_id` int(11) NOT NULL,
  `xps` int(10) unsigned NOT NULL,
  `level` int(11) NOT NULL,
  `name` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `xps` (`seminary_id`,`xps`),
  UNIQUE KEY `level` (`level`,`seminary_id`),
  KEY `created_user_id` (`created_user_id`),
  KEY `seminary_id` (`seminary_id`),
  CONSTRAINT `xplevels_ibfk_1` FOREIGN KEY (`created_user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `xplevels_ibfk_2` FOREIGN KEY (`seminary_id`) REFERENCES `seminaries` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping routines for database 'z'
--
/*!50003 DROP PROCEDURE IF EXISTS `update_cache_charactergroups` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
CREATE DEFINER=`z`@`%` PROCEDURE `update_cache_charactergroups`(
	IN CHARACTERGROUPID INT(11)
)
BEGIN
	/* XPs */
	REPLACE INTO cache_charactergroups
	(charactergroup_id, xps)
	SELECT charactergroups.id, IFNULL(SUM(ROUND(charactergroupsquests.xps * charactergroupsquests_groups.xps_factor)),0) AS xps
	FROM charactergroups
	LEFT JOIN charactergroupsquests_groups ON charactergroupsquests_groups.charactergroup_id = charactergroups.id
	LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id
	WHERE charactergroups.id = CHARACTERGROUPID;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `update_cache_charactergroups_charactergroupsquest` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
CREATE DEFINER=`z`@`%` PROCEDURE `update_cache_charactergroups_charactergroupsquest`(
	IN CHARACTERGROUPSQUESTID INT(11)
)
BEGIN
	DECLARE CHARACTERGROUPID INT;
	DECLARE done INT DEFAULT FALSE;
	DECLARE charactergroups_cursor CURSOR FOR
		SELECT charactergroup_id
		FROM charactergroupsquests_groups
		WHERE charactergroupsquest_id = CHARACTERGROUPSQUESTID;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
	SET done = 0;
	OPEN charactergroups_cursor;
	get_charactergroups: LOOP
		FETCH charactergroups_cursor INTO CHARACTERGROUPID;
		IF done = TRUE THEN
			LEAVE get_charactergroups;
		END IF;
		CALL update_cache_charactergroups(CHARACTERGROUPID);
	END LOOP get_charactergroups;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `update_cache_characters` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
CREATE DEFINER=`z`@`%` PROCEDURE `update_cache_characters`(
	IN CHARACTERID INT(11)
)
BEGIN
	DECLARE QUESTXPS INT UNSIGNED;
	DECLARE GROUPSXPS INT UNSIGNED;
	DECLARE TOTALXPS INT UNSIGNED;
	DECLARE XPLEVELID INT;
	DECLARE AVATARID INT;
	
	/* XPs */
	SELECT IFNULL(SUM(quests.xps),0) INTO QUESTXPS
	FROM quests_characters
	LEFT JOIN quests ON quests.id = quests_characters.quest_id
	WHERE quests_characters.character_id = CHARACTERID AND quests_characters.status = 3;
	SELECT IFNULL(SUM(cache_charactergroups.xps),0) INTO GROUPSXPS
	FROM characters_charactergroups
	LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = characters_charactergroups.charactergroup_id
	WHERE characters_charactergroups.character_id = CHARACTERID;
	SET TOTALXPS = QUESTXPS + GROUPSXPS;

	/* XP-level */
	SELECT (
		SELECT id
		FROM xplevels
		WHERE seminary_id = charactertypes.seminary_id AND xps = (
			SELECT MAX(xps)
			FROM xplevels AS xplevels_sub
			WHERE xps <= TOTALXPS
		)
	) INTO XPLEVELID
	FROM characters
	LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id
	WHERE characters.id = CHARACTERID;
	
	/* Avatar */
	SELECT avatars.id INTO AVATARID
	FROM characters
	LEFT JOIN avatars ON avatars.charactertype_id = characters.charactertype_id AND avatars.xplevel_id = XPLEVELID
	WHERE characters.id = CHARACTERID;
	
	/* Set values */
	REPLACE INTO cache_characters
	(character_id, xps, quest_xps, xplevel_id, avatar_id)
	VALUES
	(CHARACTERID, TOTALXPS, QUESTXPS, XPLEVELID, AVATARID);
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `update_cache_characters_charactergroup` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
CREATE DEFINER=`z`@`%` PROCEDURE `update_cache_characters_charactergroup`(
	IN CHARACTERGROUPID INT(11)
)
BEGIN
	DECLARE CHARACTERID INT;
	DECLARE done INT DEFAULT FALSE;
	DECLARE characters_cursor CURSOR FOR
		SELECT character_id
		FROM characters_charactergroups
		WHERE charactergroup_id = CHARACTERGROUPID;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
	SET done = 0;
	OPEN characters_cursor;
	get_characters: LOOP
		FETCH characters_cursor INTO CHARACTERID;
		IF done = TRUE THEN
			LEAVE get_characters;
		END IF;
		CALL update_cache_characters(CHARACTERID);
	END LOOP get_characters;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `update_cache_characters_quest` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_unicode_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
CREATE DEFINER=`z`@`%` PROCEDURE `update_cache_characters_quest`(
	IN QUESTID INT(11)
)
BEGIN
	DECLARE CHARACTERID INT;
	DECLARE done INT DEFAULT FALSE;
	DECLARE characters_cursor CURSOR FOR
		SELECT character_id
		FROM quests_characters
		WHERE quest_id = QUESTID AND status = 3;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
	SET done = 0;
	OPEN characters_cursor;
	get_characters: LOOP
		FETCH characters_cursor INTO CHARACTERID;
		IF done = TRUE THEN
			LEAVE get_characters;
		END IF;
		CALL update_cache_characters(CHARACTERID);
	END LOOP get_characters;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-05-19 11:52:32
