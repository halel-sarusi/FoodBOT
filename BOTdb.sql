-- MySQL dump 10.13  Distrib 8.0.19, for Win64 (x86_64)
--
-- Host: localhost    Database: bot_db
-- ------------------------------------------------------
-- Server version	8.0.19

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `allergies`
--

DROP TABLE IF EXISTS `allergies`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `allergies` (
  `id_user` int NOT NULL,
  `Lactose` tinyint(1) NOT NULL,
  `G6PD` tinyint(1) NOT NULL,
  `nuts` tinyint(1) NOT NULL,
  `gluten` tinyint(1) NOT NULL,
  PRIMARY KEY (`id_user`),
  CONSTRAINT `users_allergies` FOREIGN KEY (`id_user`) REFERENCES `users` (`id_user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `allergies`
--

LOCK TABLES `allergies` WRITE;
/*!40000 ALTER TABLE `allergies` DISABLE KEYS */;
INSERT INTO `allergies` VALUES (2,1,0,0,0),(5,0,1,0,0);
/*!40000 ALTER TABLE `allergies` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dish`
--

DROP TABLE IF EXISTS `dish`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dish` (
  `id` int NOT NULL AUTO_INCREMENT,
  `food` varchar(45) NOT NULL,
  `vegetarian` varchar(45) NOT NULL,
  `Lactose` tinyint(1) DEFAULT NULL,
  `G6PD` tinyint(1) DEFAULT NULL,
  `nuts` tinyint(1) DEFAULT NULL,
  `gluten` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dish`
--

LOCK TABLES `dish` WRITE;
/*!40000 ALTER TABLE `dish` DISABLE KEYS */;
INSERT INTO `dish` VALUES (1,'Cheesecake','1',1,0,0,1),(2,'Soy beans','1',0,1,0,0),(3,'yogurt','1',1,0,0,0),(4,'salmon fish','1',0,0,0,0),(5,'Stretched fish','1',0,0,0,0),(6,'tuna fish','1',0,0,0,0),(7,'Tomato pasta','1',0,0,0,1),(8,'Pizza with tuna','1',1,0,0,1),(9,'Pasta Alfredo','1',1,0,0,1),(10,'Pasta Rosa','1',1,0,0,1),(11,'Regular pizza','1',1,0,0,1),(12,'Pizza with olives','1',1,0,0,1),(13,'Pizza with pepperoni','0',1,0,0,1),(14,'Hamburger with cheese','0',1,0,0,1),(15,'chicken in the oven','0',0,0,0,0),(16,'Schnitzel in a baguette','0',0,0,0,1),(17,'Beef burger','0',0,0,0,1),(18,'Steak on a plate','0',0,0,0,0),(19,'Survivors and French fries','0',0,0,0,0),(20,'Stuffed with rice and vegetables','1',0,0,0,0),(21,'Chicken skewers','0',0,0,0,0),(22,'Stuffed with beef','0',0,0,0,0),(23,'Caesar salad (with nuts)','1',1,0,1,0),(24,'Tuna salad','1',0,0,0,0),(25,'Israeli salad','1',0,0,0,0),(26,'soup','1',0,0,0,0),(27,'American ice cream','1',1,0,0,0);
/*!40000 ALTER TABLE `dish` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dish_restaurant`
--

DROP TABLE IF EXISTS `dish_restaurant`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dish_restaurant` (
  `id` int NOT NULL AUTO_INCREMENT,
  `dish_id` int NOT NULL,
  `restaurant_id` int NOT NULL,
  PRIMARY KEY (`id`,`dish_id`,`restaurant_id`),
  KEY `dish-id` (`dish_id`),
  KEY `restaurant-id` (`restaurant_id`),
  CONSTRAINT `dish-id` FOREIGN KEY (`dish_id`) REFERENCES `dish` (`id`),
  CONSTRAINT `restaurant-id` FOREIGN KEY (`restaurant_id`) REFERENCES `restaurant` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dish_restaurant`
--

LOCK TABLES `dish_restaurant` WRITE;
/*!40000 ALTER TABLE `dish_restaurant` DISABLE KEYS */;
INSERT INTO `dish_restaurant` VALUES (3,3,4),(4,4,3),(5,5,3),(6,6,3),(7,7,1),(8,8,1),(9,9,1),(10,10,1),(11,11,2),(12,12,2),(13,13,2),(14,14,5),(15,15,5),(16,16,5),(17,17,6),(18,18,6),(19,19,6),(20,20,6),(21,21,5),(22,22,5),(23,23,1),(24,24,2),(25,25,2),(26,26,7),(27,27,4);
/*!40000 ALTER TABLE `dish_restaurant` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `orders` (
  `ID_order` int NOT NULL AUTO_INCREMENT,
  `id_user` int NOT NULL,
  `dish_restaurant_id` int NOT NULL,
  `date` date NOT NULL,
  `status` varchar(45) NOT NULL,
  PRIMARY KEY (`ID_order`,`id_user`,`dish_restaurant_id`),
  KEY `id_user_idx` (`id_user`),
  KEY `dish-restaurant_idx` (`dish_restaurant_id`),
  CONSTRAINT `dish_restaurant2` FOREIGN KEY (`dish_restaurant_id`) REFERENCES `dish_restaurant` (`id`),
  CONSTRAINT `id_user` FOREIGN KEY (`id_user`) REFERENCES `users` (`id_user`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (1,1,3,'2020-02-15','Completed'),(2,1,3,'2020-06-13','Completed'),(3,2,8,'2020-12-21','Completed'),(4,3,10,'2020-12-30','Completed'),(5,4,15,'2021-01-01','Completed'),(6,4,20,'2020-01-18','in process'),(7,5,6,'2021-02-26','Ordered'),(8,5,27,'2021-02-27','Ordered'),(9,5,6,'2021-02-28','Ordered');
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `restaurant`
--

DROP TABLE IF EXISTS `restaurant`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `restaurant` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Restaurant` varchar(45) NOT NULL,
  `cosher` tinyint(1) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `ID_idx` (`ID`),
  CONSTRAINT `ID` FOREIGN KEY (`ID`) REFERENCES `dish` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `restaurant`
--

LOCK TABLES `restaurant` WRITE;
/*!40000 ALTER TABLE `restaurant` DISABLE KEYS */;
INSERT INTO `restaurant` VALUES (1,'pizza - liza',1),(2,'pizza - hasan',0),(3,'Dan the fisherman',1),(4,'desserts',1),(5,'Herzl skewers',0),(6,'Bird skewers',1),(7,'shemesh',1);
/*!40000 ALTER TABLE `restaurant` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id_user` int NOT NULL AUTO_INCREMENT,
  `first_name` varchar(45) NOT NULL,
  `last_name` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  `adress` varchar(45) DEFAULT NULL,
  `phone` varchar(45) DEFAULT NULL,
  `credit` varchar(45) DEFAULT NULL,
  `cosher` tinyint(1) NOT NULL,
  `allergies` tinyint(1) NOT NULL,
  `vegetarian` tinyint(1) NOT NULL,
  PRIMARY KEY (`id_user`)
) ENGINE=InnoDB AUTO_INCREMENT=45 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'bar','asher','123','tamar 81','0526151328','951236845',1,0,0),(2,'golan','or','456','elat 94','0503020615','456654987',1,1,0),(3,'omer','lev','789','goshen 3','0549080613','123465987',0,0,1),(4,'ora','chen','101','bar-gol 63','0546358749','5123069845',1,0,1),(5,'halel','sarusi','1563','goshen 3','0545693030','9523596',1,1,0);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-03-01 15:59:47
