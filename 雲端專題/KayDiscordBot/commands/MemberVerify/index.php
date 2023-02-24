<?php 

$text= $_POST["text"];
// data strored in array


// $hostname = "ec2-52-2-118-38.compute-1.amazonaws.com";
// $dbname = "dfdobug1c771t2";
// $username = "cbynnhmmgimwaq";
// $pass = "3d7fc902098189e0744a6ec5a9c84904af2cd1607c297488d51fda4654c6c518";
// $port = 5432

$hostname = "discordbotdatabase.czhutqsbjfeu.us-east-1.rds.amazonaws.com";
$dbname = "postgres";
$username = "kay";
$pass = "asx5566789";
# $port = "5432"


// CREATE the connection TO the PostgreSQL
$db_conn = pg_connect(" host = $hostname dbname = $dbname user = $username password = $pass ");


$result = pg_query($db_conn, "SELECT * FROM discord_Yue");

while ($row = pg_fetch_row($result)) {
  if($row[0]==$text)
  {	
	  $temp="";
	  for($i=0;$i<10;$i++)
		$temp=$temp.rand(0,9);
	  
	  echo "驗證碼: ".$temp;
	  
	  //$query = pg_query($db_conn, "INSERT  INTO users(first_name, last_name) VALUES ('$fname','$lname');");
	  $query = pg_query($db_conn, "UPDATE discord_Yue SET code = ('$temp')");
	  
  }
  else
	echo "驗證錯誤";
  break;
}


?>