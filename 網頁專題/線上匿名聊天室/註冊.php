<!DOCTYPE html>
<html>
   <head><meta charset = "utf-8"><title>Search Results</title>
   <style>
	 .FailandSuc
	 {
		 color:red;
		 width:50%;
		 height:50%;
		 font-size:100px;
		 font-weight:bold;
		 position:relative;
		 margin-top:10px;
		 margin-left:370px;
	 }
	 .result
	 {
		 color:red;
		 width:50%;
		 height:50%;
		 font-size:100px;
		 font-weight:bold;
		 position:relative;
		 margin-top:150px;
		 margin-left:490px;
	 }
	 body
	 {
		background:url('SuccessAndFalse.png') rgb(0,0,0,0.5);
		background-repeat: no-repeat;
		background-attachment:fixed;
		background-size:100%;
		background-position:55% 75%;
	 }
	 a           
	  { 
		font-weight: bold;
		font-size:25px;
		color: white;
		border: 2px solid RoyalBlue;
		text-align: center;
		width: 10em;
		background-color: RoyalBlue; 
		float:left;
	  }				
      a:hover       
	  {
		 background-color:red;
	  }
	  div.head
	  {
			position:relative;
			margin-left:410px;
			background-color:RoyalBlue;
	  }
   </style>
   </head>
   <body>
	  <?php
	   $name=$_POST["name"];
	   $sex=$_POST["sex"];
	   $telephone=$_POST["tel"];
	   $email=$_POST["email"];
	   $account=$_POST["account"];
	   $password=$_POST["password"];
	   $answer=$_POST["question"];
	   use PHPMailer\PHPMailer\PHPMailer;
	   use PHPMailer\PHPMailer\Exception;
	   if($answer=="蒙奇D魯夫")
	   {
		  $query = "INSERT INTO `memberdata`( `account`, `password`,`姓名`,`性別`,`電話`,`信箱` ) VALUES('". $account ."','". $password ."','".$name."','".$sex."','".$telephone."','".$email."')"; 
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
			  print( "<script>alert('此帳號已經存在！!');history.back();</script>");
		  } 
		  else
		  {
		     if ( !( $result = mysqli_query($database, $query) ) )
		     {
		     	  print( "<p>Could not execute query!</p>" );
				  die( mysqli_error() . "</body></html>" );
		     }
			 
			  mysqli_close( $database ); 
		   print('<div class="head">');
	       print('<a href="會員註冊.html">註冊 </a>');
	       print( '<a href="聊天室登入頁面.html">登入</a>');
		   print('</div><br><br>');
		   print("<div class='result'>註冊成功</div>");
		   print("<div class='FailandSuc'>去和肥宅交流!</div>");
		    
		   /*---------------- Sent Mail Start -----------------*/ 
			
			
			require 'PHPMailer/src/Exception.php';
			require 'PHPMailer/src/PHPMailer.php';
			require 'PHPMailer/src/SMTP.php';
			$name=$_POST["name"];
			$email=$_POST["email"];
			$mail = new PHPMailer(true);                              // Passing `true` enables exceptions
			try {
				//伺服器配置
				$mail->CharSet ="UTF-8";					 //設定郵件編碼
				$mail->SMTPDebug = 0;                        // 除錯模式輸出
				$mail->isSMTP();                             // 使用SMTP
				$mail->Host = 'smtp.gmail.com';                // SMTP伺服器
				$mail->SMTPAuth = true;                      // 允許 SMTP 認證
				$mail->Username = 'asx5566123';                // SMTP 使用者名稱  即郵箱的使用者名稱asx5566123@gmail.com
				$mail->Password = 'asx5566789';             // SMTP 密碼  部分郵箱是授權碼(例如163郵箱)
				$mail->SMTPSecure = 'ssl';                    // 允許 TLS 或者ssl協議
				$mail->Port = 465;                            // 伺服器埠 25 或者465 具體要看郵箱伺服器支援

				$mail->setFrom('asx5566123@gmail.com', '肥宅聊天室會員管理處');  //發件人
				$mail->addAddress($email, $name);  // 收件人
				//$mail->addAddress('ellen@example.com');  // 可新增多個收件人
				$mail->addReplyTo('asx5566123@gmail.com', 'info'); //回覆的時候回覆給哪個郵箱 建議和發件人一致
				//$mail->addCC('cc@example.com');					//抄送
				//$mail->addBCC('bcc@example.com');					//密送
				
				//Content
				$mail->isHTML(true);                                  // 是否以HTML文件格式傳送  傳送後客戶端可直接顯示對應HTML內容
				$mail->Subject = '肥宅聊天室的會員認證信';
				$mail->Body    = '
				<html>
								<head>
								</head>
								<body>
								<h1>'.$_POST['name'].'先生/小姐</h1>
								<p>感謝支持肥宅聊天室</p>
								<p>請確認您的資料</p>
								<p><h>姓名:</h>'.$_POST['name'].'</p>
								<p><h>性別:</h>'.$_POST['sex'].'</p>
								<p><h>電話:</h>'.$_POST['tel'].'</p>
								</body>
								 </html>';
				$mail->AltBody = '如果郵件客戶端不支援HTML則顯示此內容';

				$mail->send();
				//echo '郵件傳送成功';
			} catch (Exception $e) {
				echo '郵件傳送失敗: ', $mail->ErrorInfo;
			}  
			/*---------------- Sent Mail End -------------------*/
			 
		  }

		  
	   }
	   else
	   {
		   print('<div class="head">');
	       print('<a href="會員註冊.html">註冊 </a>');
	       print( '<a href="聊天室登入頁面.html">登入</a>');
		   print('</div><br><br>');
		   print("<div  class='result'>註冊失敗</div>");
		   print("<div class='FailandSuc'>去多看點動漫!</div>");
		  
	   }
	?>
   </body>
</html>

