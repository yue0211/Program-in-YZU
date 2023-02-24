<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Chat System</title>
    <style>
	  object
	  {
		 object-fit:fill;
		  width:0%;
		 height:0%;

		  
	  }
      body{
		  font-size:20px;
		  font-weight:bold;
		  background:url('對話背景.png') rgb(0,0,0,0.5);
		  background-repeat: no-repeat;
		  background-attachment:fixed;
		  background-position:55% 55%;

	  }
	  #message
	  {
		  position:relative;
		  margin-top:20px;
		  width:500px;
		  height:200px;
		  
	  }
	  .chathistory
	  {
		  padding:15px;
		  
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
			
			background-color:RoyalBlue;
	  }
	</style>
	<script
		src="https://code.jquery.com/jquery-3.3.1.js"
		integrity="sha256-2Kok7MbOyxpgUVvAk/HJ2jigOSYS2auK4Pfzbm7uH60="
		crossorigin="anonymous">
		 
 
  </script>
</head>
<body>

	<div class="head">
	  <a href="聊天室登入頁面.html">登出</a>
     </div>
	 <br><br>
	<div class="centeralised">
	
	<div class="chathistory"></div>
	<div class="chatbox">
		
		<form action="" method="POST">
			
			<textarea class="txtarea" id="message" name="message"></textarea>
		</form>
	</div>
	</div>
	<p>
	<audio src="EVE歌曲.mp3" autoplay controls></audio>
	</p>
	<script>
		$(document).ready(function(){
			loadChat();
			
		});
		
		$('#message').keyup(function(e){
			var message = $(this).val();
			if( e.which == 13 ){
				$.post('ajax.php?action=SendMessage&message='+message, function(response){
					
					loadChat();
					$('#message').val('');
				});
			}
		});
		function loadChat()
		{
			$.post('ajax.php?action=getChat', function(response){
				
				$('.chathistory').html(response);
			});
		}
		setInterval(function(){
			loadChat();
		}, 2000);
	</script>
</body>
</html>