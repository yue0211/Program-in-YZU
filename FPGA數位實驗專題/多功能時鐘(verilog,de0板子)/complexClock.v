module complexClock(led,hex3,hex2,hex1,hex0,button2,button1,button0,switch,clk);

input button2,button1,button0,clk;
input [4:0] switch; 
output reg [7:0] hex3;//輸出最終七段顯示器的結果
output reg [7:0] hex2;
output reg [7:0] hex1;
output reg [7:0] hex0;
output reg [9:0] led=10'b0000000000;//輸出最終燈的結果

reg [9:5] fire;
reg [4:0] fire2=5'b01000;
reg [4:0] fire3=5'b01000;
reg [4:0] fire4=5'b00000;

reg [7:0] replacehex3;
reg [7:0] replacehex2;
reg [7:0] replacehex1;
reg [7:0] replacehex0;

reg [7:0] temphex3;
reg [7:0] temphex2;
reg [7:0] temphex1;
reg [7:0] temphex0;


reg [7:0] horsehex3;
reg [7:0] horsehex2;
reg [7:0] horsehex1;
reg [7:0] horsehex0;

reg [7:0] replace2hex3;
reg [7:0] replace2hex2;
reg [7:0] replace2hex1;
reg [7:0] replace2hex0;

reg [7:0] lasthex3;
reg [7:0] lasthex2;
reg [7:0] lasthex1;
reg [7:0] lasthex0;


reg [5:0] value; // 60 units
reg [5:0] value2; // 倒數計時用

reg [25:0]counter;

reg [3:0]number3; 
reg [3:0]number2;
reg [3:0]number1;
reg [3:0]number0;

reg [3:0] minuteFirst;
reg [3:0] minuteSecond;
reg [3:0] hrFirst;
reg [3:0] hrSecond;


reg [3:0] horseminuteFirst=4'b0000;
reg [3:0] horseminuteSecond=4'b0000;
reg [3:0] horsehrFirst=4'b0000;
reg [3:0] horsehrSecond=4'b0000;


reg [3:0]number7; 
reg [3:0]number6;
reg [3:0]number5;
reg [3:0]number4;

reg [3:0] lastminuteFirst;
reg [3:0] lastminuteSecond;
reg [3:0] lasthrFirst;
reg [3:0] lasthrSecond;


reg [1:0]mark=2'b00;
reg [1:0]mark2=2'b00;
reg [2:0]set;
reg [1:0]settemp=2'b00;
reg start=0;
reg start2=0;
reg reset=0;
reg half;

wire out3;
wire out4;


always @(switch)
begin
 case(switch)
	 5'b00001:
	 begin
	   set<=0;
	   fire<=5'b00001;
	 end
	 5'b00010:
	 begin
	   set<=1;
	   fire<=5'b00010;
	 end
	 5'b00100:
	 begin
	   set<=2;
	   fire<=5'b00100;
	 end
	 5'b01000:
	 begin
	   set<=3;
	   fire<=5'b01000;
	 end
	 5'b10000:
	 begin
	   set<=4;
	   fire<=5'b10000;
	 end
	 default:
	 begin
	   set<=5;
	   fire<=5'b00000;
	 end
 endcase
end


always @(posedge clk)
begin
 if(counter==25'd25000000)
 begin
  counter<=0;
  half=~half;
 end
 else
  counter<=counter+1;
end

always @(posedge half)
begin
	fire4<=5'b00000;//
	if(set==0)
	begin
	  minuteFirst<=number0;
	  minuteSecond<=number1;
	  hrFirst<=number2;
	  hrSecond<=number3;
	end	
	else if(set==1)
	begin
	 if(value==59)
	 begin
		value<=0;
		
		if(minuteFirst==9)
		begin
		 minuteFirst<=0;
		  if(minuteSecond==5)
		  begin
			minuteSecond<=0;
			if(hrFirst==9&&hrSecond!=2)
			begin
			 hrFirst<=0;
			 hrSecond<=hrSecond+1;
			end
			else if(hrSecond==2&&hrFirst==3)
			begin
				minuteFirst<=0;
				minuteSecond<=0; 
				hrFirst<=0;
				hrSecond<=0; 
			end
			else
			 hrFirst<=hrFirst+1;
		  end
		  else
			minuteSecond<=minuteSecond+1;
		end
		else
		 minuteFirst<=minuteFirst+1;
	 end
	 else
	   value<=value+1;
	end
	else if(set==2)
	begin
	 if(start==1)
	 begin
	    if(horseminuteFirst==9)
		begin
		 horseminuteFirst<=0;
		 if(horseminuteSecond==5)
		 begin
			horseminuteSecond<=0;
			if(horsehrFirst==9)
		    begin
			  horsehrFirst<=0;
			  if(horsehrSecond==9)
			  begin
			    horseminuteFirst<=0;
			    horseminuteSecond<=0;
			    horsehrFirst<=0;
			    horsehrSecond<=0;
			  end
			  else
			   horsehrSecond<=horsehrSecond+1;
		    end
		    else
		      horsehrFirst<=horsehrFirst+1;
		 end
		 else
		  horseminuteSecond<=horseminuteSecond+1;
		end
		else
		 horseminuteFirst<=horseminuteFirst+1;
	 end
	 else if(start==0)
	 begin
	  if(reset==1)
	  begin
	     horseminuteFirst<=0;
	     horseminuteSecond<=0;
	     horsehrFirst<=0;
	     horsehrSecond<=0;
	  end
	 end
	end
	else if(set==3)
	begin
	  lastminuteFirst<=number4;
	  lastminuteSecond<=number5;
	  lasthrFirst<=number6;
	  lasthrSecond<=number7;
	end	
	else if(set==4)
	begin
      if(start2==1)/////////
	  begin
	    if(lastminuteFirst==0)
		begin
		  
		  if(lastminuteSecond==0)
		  begin
			if(lasthrFirst==0)
		    begin
				if(lasthrSecond!=0)
				begin
				 lasthrSecond<=lasthrSecond-1;
				 lasthrFirst<=9;
				 lastminuteSecond<=5;
				 lastminuteFirst<=9;
				end
				else
				  fire4<=5'b11111;
		    end
		    else
		    begin
				lasthrFirst<=lasthrFirst-1;
		    	lastminuteSecond<=5;
		    	lastminuteFirst<=9;
            end
		  end
		  else
		  begin
		   lastminuteSecond<=lastminuteSecond-1;
		   lastminuteFirst<=9;
		  end
		end
		else
		 lastminuteFirst<=lastminuteFirst-1;
      end		 
	end
	

end

////////////////////////////////////////////////////////////
always @(negedge out3)
begin
    if(set==0)
    begin
	  if(mark==0)
	  begin
	   if(number3==9)
		number3<=0;
	   else
		number3<=number3+1;
	  end
	  else if(mark==1)
	  begin
	   if(number2==9)
		number2<=0;
	   else
		number2<=number2+1;
	  end
	  else if(mark==2)
	  begin
	   if(number1==9)
		number1<=0;
	   else
		number1<=number1+1;
	  end
	  else if(mark==3)
	  begin
	   if(number0==9)
		number0<=0;
	   else
		number0<=number0+1;
	  end
   end
   else if(set==3)
    begin
	  if(mark2==0)
	  begin
	   if(number7==9)
		number7<=0;
	   else
		number7<=number7+1;
	  end
	  else if(mark2==1)
	  begin
	   if(number6==9)
		number6<=0;
	   else
		number6<=number6+1;
	  end
	  else if(mark2==2)
	  begin
	   if(number5==9)
		number5<=0;
	   else
		number5<=number5+1;
	  end
	  else if(mark2==3)
	  begin
	   if(number4==9)
		number4<=0;
	   else
		number4<=number4+1;
	  end
   end
   
   
   
   
end



always @(number3,hrSecond,horsehrSecond,number7,lasthrSecond)
begin
	 if(set==0)
	 begin
	 case(number3)
		4'b0000:replacehex3=8'b11000000;   // 0  
		4'b0001:replacehex3=8'b11111001;   // 1
		4'b0010:replacehex3=8'b10100100;   // 2
		4'b0011:replacehex3=8'b10110000;   // 3
		4'b0100:replacehex3=8'b10011001;   // 4
		4'b0101:replacehex3=8'b10010010;   // 5
		4'b0110:replacehex3=8'b10000010;   // 6
		4'b0111:replacehex3=8'b11011000;   // 7
		4'b1000:replacehex3=8'b10000000;   // 8
		4'b1001:replacehex3=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==1)
	 begin
		 case(hrSecond)
			4'b0000:temphex3=8'b11000000;   // 0  
			4'b0001:temphex3=8'b11111001;   // 1
			4'b0010:temphex3=8'b10100100;   // 2
			4'b0011:temphex3=8'b10110000;   // 3
			4'b0100:temphex3=8'b10011001;   // 4
			4'b0101:temphex3=8'b10010010;   // 5
			4'b0110:temphex3=8'b10000010;   // 6
			4'b0111:temphex3=8'b11011000;   // 7
			4'b1000:temphex3=8'b10000000;   // 8
			4'b1001:temphex3=8'b10010000;   // 9
		 endcase
	 end
	 else if(set==2)
	 begin
		 case(horsehrSecond)
			4'b0000:horsehex3=8'b11000000;   // 0  
			4'b0001:horsehex3=8'b11111001;   // 1
			4'b0010:horsehex3=8'b10100100;   // 2
			4'b0011:horsehex3=8'b10110000;   // 3
			4'b0100:horsehex3=8'b10011001;   // 4
			4'b0101:horsehex3=8'b10010010;   // 5
			4'b0110:horsehex3=8'b10000010;   // 6
			4'b0111:horsehex3=8'b11011000;   // 7
			4'b1000:horsehex3=8'b10000000;   // 8
			4'b1001:horsehex3=8'b10010000;   // 9
		 endcase
	 end
	 else if(set==3)
	 begin
	 case(number7)
		4'b0000:replace2hex3=8'b11000000;   // 0  
		4'b0001:replace2hex3=8'b11111001;   // 1
		4'b0010:replace2hex3=8'b10100100;   // 2
		4'b0011:replace2hex3=8'b10110000;   // 3
		4'b0100:replace2hex3=8'b10011001;   // 4
		4'b0101:replace2hex3=8'b10010010;   // 5
		4'b0110:replace2hex3=8'b10000010;   // 6
		4'b0111:replace2hex3=8'b11011000;   // 7
		4'b1000:replace2hex3=8'b10000000;   // 8
		4'b1001:replace2hex3=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==4)
	 begin
	 case(lasthrSecond)
		4'b0000:lasthex3=8'b11000000;   // 0  
		4'b0001:lasthex3=8'b11111001;   // 1
		4'b0010:lasthex3=8'b10100100;   // 2
		4'b0011:lasthex3=8'b10110000;   // 3
		4'b0100:lasthex3=8'b10011001;   // 4
		4'b0101:lasthex3=8'b10010010;   // 5
		4'b0110:lasthex3=8'b10000010;   // 6
		4'b0111:lasthex3=8'b11011000;   // 7
		4'b1000:lasthex3=8'b10000000;   // 8
		4'b1001:lasthex3=8'b10010000;   // 9
	 endcase
	 end
	 
end


always @(number2,hrFirst,horsehrFirst,number6,lasthrFirst)
begin
	 if(set==0)
	 begin
	 case(number2)
		4'b0000:replacehex2=8'b01000000;   // 0  
		4'b0001:replacehex2=8'b01111001;   // 1
		4'b0010:replacehex2=8'b00100100;   // 2
		4'b0011:replacehex2=8'b00110000;   // 3
		4'b0100:replacehex2=8'b00011001;   // 4
		4'b0101:replacehex2=8'b00010010;   // 5
		4'b0110:replacehex2=8'b00000010;   // 6
		4'b0111:replacehex2=8'b01011000;   // 7
		4'b1000:replacehex2=8'b00000000;   // 8
		4'b1001:replacehex2=8'b00010000;   // 9
	 endcase
	 end
	 else if(set==1)
	 begin
	 case(hrFirst)
		4'b0000:temphex2=8'b01000000;   // 0  
		4'b0001:temphex2=8'b01111001;   // 1
		4'b0010:temphex2=8'b00100100;   // 2
		4'b0011:temphex2=8'b00110000;   // 3
		4'b0100:temphex2=8'b00011001;   // 4
		4'b0101:temphex2=8'b00010010;   // 5
		4'b0110:temphex2=8'b00000010;   // 6
		4'b0111:temphex2=8'b01011000;   // 7
		4'b1000:temphex2=8'b00000000;   // 8
		4'b1001:temphex2=8'b00010000;   // 9
	 endcase
	 end
	 else if(set==2)
	 begin
	 case(horsehrFirst)
		4'b0000:horsehex2=8'b01000000;   // 0  
		4'b0001:horsehex2=8'b01111001;   // 1
		4'b0010:horsehex2=8'b00100100;   // 2
		4'b0011:horsehex2=8'b00110000;   // 3
		4'b0100:horsehex2=8'b00011001;   // 4
		4'b0101:horsehex2=8'b00010010;   // 5
		4'b0110:horsehex2=8'b00000010;   // 6
		4'b0111:horsehex2=8'b01011000;   // 7
		4'b1000:horsehex2=8'b00000000;   // 8
		4'b1001:horsehex2=8'b00010000;   // 9
	 endcase
	 end
	 else if(set==3)
	 begin
	 case(number6)
		4'b0000:replace2hex2=8'b01000000;   // 0  
		4'b0001:replace2hex2=8'b01111001;   // 1
		4'b0010:replace2hex2=8'b00100100;   // 2
		4'b0011:replace2hex2=8'b00110000;   // 3
		4'b0100:replace2hex2=8'b00011001;   // 4
		4'b0101:replace2hex2=8'b00010010;   // 5
		4'b0110:replace2hex2=8'b00000010;   // 6
		4'b0111:replace2hex2=8'b01011000;   // 7
		4'b1000:replace2hex2=8'b00000000;   // 8
		4'b1001:replace2hex2=8'b00010000;   // 9
	 endcase
	 end
	 else if(set==4)
	 begin
	 case(lasthrFirst)
		4'b0000:lasthex2=8'b01000000;   // 0  
		4'b0001:lasthex2=8'b01111001;   // 1
		4'b0010:lasthex2=8'b00100100;   // 2
		4'b0011:lasthex2=8'b00110000;   // 3
		4'b0100:lasthex2=8'b00011001;   // 4
		4'b0101:lasthex2=8'b00010010;   // 5
		4'b0110:lasthex2=8'b00000010;   // 6
		4'b0111:lasthex2=8'b01011000;   // 7
		4'b1000:lasthex2=8'b00000000;   // 8
		4'b1001:lasthex2=8'b00010000;   // 9
	 endcase
	 end
	 
	 
end



always @(number1,minuteSecond,horseminuteSecond,number5,lastminuteSecond)
begin
	 if(set==0)
	 begin
	 case(number1)
		4'b0000:replacehex1=8'b11000000;   // 0  
		4'b0001:replacehex1=8'b11111001;   // 1
		4'b0010:replacehex1=8'b10100100;   // 2
		4'b0011:replacehex1=8'b10110000;   // 3
		4'b0100:replacehex1=8'b10011001;   // 4
		4'b0101:replacehex1=8'b10010010;   // 5
		4'b0110:replacehex1=8'b10000010;   // 6
		4'b0111:replacehex1=8'b11011000;   // 7
		4'b1000:replacehex1=8'b10000000;   // 8
		4'b1001:replacehex1=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==1)
	 begin
	 case(minuteSecond)
		4'b0000:temphex1=8'b11000000;   // 0  
		4'b0001:temphex1=8'b11111001;   // 1
		4'b0010:temphex1=8'b10100100;   // 2
		4'b0011:temphex1=8'b10110000;   // 3
		4'b0100:temphex1=8'b10011001;   // 4
		4'b0101:temphex1=8'b10010010;   // 5
		4'b0110:temphex1=8'b10000010;   // 6
		4'b0111:temphex1=8'b11011000;   // 7
		4'b1000:temphex1=8'b10000000;   // 8
		4'b1001:temphex1=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==2)
	 begin
	 case(horseminuteSecond)
		4'b0000:horsehex1=8'b11000000;   // 0  
		4'b0001:horsehex1=8'b11111001;   // 1
		4'b0010:horsehex1=8'b10100100;   // 2
		4'b0011:horsehex1=8'b10110000;   // 3
		4'b0100:horsehex1=8'b10011001;   // 4
		4'b0101:horsehex1=8'b10010010;   // 5
		4'b0110:horsehex1=8'b10000010;   // 6
		4'b0111:horsehex1=8'b11011000;   // 7
		4'b1000:horsehex1=8'b10000000;   // 8
		4'b1001:horsehex1=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==3)
	 begin
	 case(number5)
		4'b0000:replace2hex1=8'b11000000;   // 0  
		4'b0001:replace2hex1=8'b11111001;   // 1
		4'b0010:replace2hex1=8'b10100100;   // 2
		4'b0011:replace2hex1=8'b10110000;   // 3
		4'b0100:replace2hex1=8'b10011001;   // 4
		4'b0101:replace2hex1=8'b10010010;   // 5
		4'b0110:replace2hex1=8'b10000010;   // 6
		4'b0111:replace2hex1=8'b11011000;   // 7
		4'b1000:replace2hex1=8'b10000000;   // 8
		4'b1001:replace2hex1=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==4)
	 begin
	 case(lastminuteSecond)
		4'b0000:lasthex1=8'b11000000;   // 0  
		4'b0001:lasthex1=8'b11111001;   // 1
		4'b0010:lasthex1=8'b10100100;   // 2
		4'b0011:lasthex1=8'b10110000;   // 3
		4'b0100:lasthex1=8'b10011001;   // 4
		4'b0101:lasthex1=8'b10010010;   // 5
		4'b0110:lasthex1=8'b10000010;   // 6
		4'b0111:lasthex1=8'b11011000;   // 7
		4'b1000:lasthex1=8'b10000000;   // 8
		4'b1001:lasthex1=8'b10010000;   // 9
	 endcase
	 end
	 
	 
end


always @(number0,minuteFirst,horseminuteFirst,number4,lastminuteFirst)
begin
     if(set==0)
	 begin
	 case(number0)
		4'b0000:replacehex0=8'b11000000;   // 0  
		4'b0001:replacehex0=8'b11111001;   // 1
		4'b0010:replacehex0=8'b10100100;   // 2
		4'b0011:replacehex0=8'b10110000;   // 3
		4'b0100:replacehex0=8'b10011001;   // 4
		4'b0101:replacehex0=8'b10010010;   // 5
		4'b0110:replacehex0=8'b10000010;   // 6
		4'b0111:replacehex0=8'b11011000;   // 7
		4'b1000:replacehex0=8'b10000000;   // 8
		4'b1001:replacehex0=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==1)
	 begin
	 case(minuteFirst)
		4'b0000:temphex0=8'b11000000;   // 0  
		4'b0001:temphex0=8'b11111001;   // 1
		4'b0010:temphex0=8'b10100100;   // 2
		4'b0011:temphex0=8'b10110000;   // 3
		4'b0100:temphex0=8'b10011001;   // 4
		4'b0101:temphex0=8'b10010010;   // 5
		4'b0110:temphex0=8'b10000010;   // 6
		4'b0111:temphex0=8'b11011000;   // 7
		4'b1000:temphex0=8'b10000000;   // 8
		4'b1001:temphex0=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==2)
	 begin
	 case(horseminuteFirst)
		4'b0000:horsehex0=8'b11000000;   // 0  
		4'b0001:horsehex0=8'b11111001;   // 1
		4'b0010:horsehex0=8'b10100100;   // 2
		4'b0011:horsehex0=8'b10110000;   // 3
		4'b0100:horsehex0=8'b10011001;   // 4
		4'b0101:horsehex0=8'b10010010;   // 5
		4'b0110:horsehex0=8'b10000010;   // 6
		4'b0111:horsehex0=8'b11011000;   // 7
		4'b1000:horsehex0=8'b10000000;   // 8
		4'b1001:horsehex0=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==3)
	 begin
	 case(number4)
		4'b0000:replace2hex0=8'b11000000;   // 0  
		4'b0001:replace2hex0=8'b11111001;   // 1
		4'b0010:replace2hex0=8'b10100100;   // 2
		4'b0011:replace2hex0=8'b10110000;   // 3
		4'b0100:replace2hex0=8'b10011001;   // 4
		4'b0101:replace2hex0=8'b10010010;   // 5
		4'b0110:replace2hex0=8'b10000010;   // 6
		4'b0111:replace2hex0=8'b11011000;   // 7
		4'b1000:replace2hex0=8'b10000000;   // 8
		4'b1001:replace2hex0=8'b10010000;   // 9
	 endcase
	 end
	 else if(set==4)
	 begin
	 case(lastminuteFirst)
		4'b0000:lasthex0=8'b11000000;   // 0  
		4'b0001:lasthex0=8'b11111001;   // 1
		4'b0010:lasthex0=8'b10100100;   // 2
		4'b0011:lasthex0=8'b10110000;   // 3
		4'b0100:lasthex0=8'b10011001;   // 4
		4'b0101:lasthex0=8'b10010010;   // 5
		4'b0110:lasthex0=8'b10000010;   // 6
		4'b0111:lasthex0=8'b11011000;   // 7
		4'b1000:lasthex0=8'b10000000;   // 8
		4'b1001:lasthex0=8'b10010000;   // 9
	 endcase
	 end
	 
	 
end

always @(set)//
begin
 if(set==0)  // replacehex0 => 放設定好的數值
 begin
  hex0<=replacehex0;
  hex1<=replacehex1;
  hex2<=replacehex2;
  hex3<=replacehex3;
  led[9:5]<=fire;
  led[4:0]<=fire2;
 end
 else if(set==1) // temphex0 => 放顯示時間的數值
 begin
  hex0<=temphex0;
  hex1<=temphex1;
  hex2<=temphex2;
  hex3<=temphex3;
  led[9:5]<=fire;
  led[4:0]<=5'b00000;
 end
 else if(set==2) // horsehex0 
 begin
  hex0<=horsehex0;
  hex1<=horsehex1;
  hex2<=horsehex2;
  hex3<=horsehex3;
  led[9:5]<=fire;
  led[4:0]<=5'b00000;
 end
 else if(set==3) 
 begin
  hex0<=replace2hex0;
  hex1<=replace2hex1;
  hex2<=replace2hex2;
  hex3<=replace2hex3;
  led[9:5]<=fire;
  led[4:0]<=fire3;
 end
 else if(set==4) 
 begin
  hex0<=lasthex0;
  hex1<=lasthex1;
  hex2<=lasthex2;
  hex3<=lasthex3;
  led[9:5]<=fire;
  led[4:0]<=fire4;
 end
 else if(set==5)
 begin
  hex0<=8'b110111111;
  hex1<=8'b110111111;
  hex2<=8'b110111111;
  hex3<=8'b110111111;
  led[9:5]<=fire;
  led[4:0]<=5'b00000;
 end
end

always @(negedge button2)
begin

 if(button2==0&&set==2&&start==0)
	start<=start+1;
 else if(button2==0&&set==2&&start==1)
    start<=start-1;
    
 if(button2==0&&set==4&&start2==0)
	start2<=start2+1;
 else if(button2==0&&set==4&&start2==1)
    start2<=start2-1;
  
end



always @(negedge button1)
begin
 if(button1==0&&set==0)
	mark<=mark+1;
 else if(button1==0&&set==3)
    mark2<=mark2+1;
end

always @(mark,mark2)
begin
	if((mark%4)==0)
	  fire2<=5'b01000;
	else if((mark%4)==1)
	  fire2<=5'b00100;
	else if((mark%4)==2)
	  fire2<=5'b00010;
	else if((mark%4)==3)
	  fire2<=5'b00001;
	  
	if((mark2%4)==0)
	  fire3<=5'b01000;
	else if((mark2%4)==1)
	  fire3<=5'b00100;
	else if((mark2%4)==2)
	  fire3<=5'b00010;
	else if((mark2%4)==3)
	  fire3<=5'b00001; 
end



always @(button1)
begin
 if(button1==0&&set==2)
  reset<=1;
 else if(button1==1&&set==2)
  reset<=0;
end


debouncing A1(button2,out3,counter[13]);


endmodule  



module debouncing(in,out,clk);

input in,clk;
output out;

reg [3:1]FF;
reg [8:0]counter2;

always @(posedge clk)
begin
 FF[1]<= in;
 FF[2]<=FF[1];

 if(FF[1]^FF[2]==1)
  counter2<=9'd0;
 else
   if(counter2<9'd511)
	counter2<=counter2+9'd1;
   else
    FF[3]<=FF[2];

end

assign out = FF[3];

endmodule 