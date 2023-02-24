<!DOCTYPE html>
<html>
	<head>
		<meta charset = "utf-8">
		<title>Search Results</title>

	</head>

    <body>
	  <?php
		$account=$_POST["account"];
	    $password=$_POST["password"];
		$peopleName=$_POST["text"];
		if ( !( $database = mysqli_connect( "localhost", "members", "members" ) ) )   
		   die( "Could not connect to database </body></html>" );				
		if ( !mysqli_select_db($database,"members" ) )
			   die( "Could not open products database </body></html>" );
		$search = 'SELECT `account`,`password` from `memberdata` where  `account`="'.$account.'" AND `password`="'.$password.'"';
	    $res=mysqli_query($database,$search);
	    if(!($res))
	    {
		   print( "<p>Could not execute query!</p>" );
		   die( mysqli_error() . "</body></html>" );
	    }
	    if(mysqli_num_rows($res)>0)
	    {
		   print( "<script>alert('已登入！!');</script>");
		   session_start();
		   $_SESSION['account']=$account;
		   $_SESSION['password']=$password;
		   $_SESSION['text']=$peopleName;
		   
		   header('Location:index.php'); 
	    } 
		else
		{
			print( "<script>alert('尚未註冊！!');history.back();</script>");
		}
		
	
	
	  ?>
	</body>
</html>