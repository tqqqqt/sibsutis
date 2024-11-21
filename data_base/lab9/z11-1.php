<html>
	<head><title>N1</title></head>
	<body>
		<?php
			$file_name="notebook_br4.txt";
			if(file_exists($file_name) && is_file($file_name)) echo "<p>Файл существует</p>";
			else touch($file_name);
			$fp=fopen($file_name,"w");

			$conn=mysqli_connect("localhost","root","");
			mysqli_select_db($conn,"sample");
			$result=mysqli_query($conn,"select * from notebook_br4;");
			$date_patern="/([0-9]{4}).([0-9]{2}).([0-9]{2})/";
			$change_patern="$3.$2.$1";
			$count_col=mysqli_num_fields($result);
			while($row=mysqli_fetch_row($result)){
				$count=0;
				foreach($row as $elem){
					$temp=$elem;
					if(preg_match($date_patern,$temp)) $temp=preg_replace($date_patern,$change_patern,$temp);
					if($count==0) fwrite($fp,"| ".$temp." | ");
					else if($count==$count_col-1) fwrite($fp,$temp." | \n");
					else fwrite($fp,$temp." | ");
					$count++;
				}
			}
			fclose($fp);

			$fp=fopen($file_name,"r");
			while(!feof($fp)){
				$temp=fgets($fp,1024);
				echo "$temp<br>";
			}
			fclose($fp);

			echo "<a href='z11-2.php'>Второе задание</a>";
		?>
	</body>
</html>