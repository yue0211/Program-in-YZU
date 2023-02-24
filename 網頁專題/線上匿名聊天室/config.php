<?php

	$dbhost = "localhost";
	$dbname = "chat_system";
	$dbuser = "asx5566123";
	$dbpass = 'asx5566789';


	try{
		$db = new PDO("mysql:dbhost=$dbhost;dbname=$dbname", "$dbuser", "$dbpass");
	}catch(PDOException $e){
		echo $e->getMessage();
	}

	



?>