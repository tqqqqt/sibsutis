<html>
	<head><title>N2</title></head>
	<body>
		<?php
			echo "<a href='z11-1.php'>Задание 1</a>";

			$file_name="notebook_br4.txt";
			if(!file_exists($file_name) || !is_file($file_name) || !is_readable($file_name)){
				echo "<a href='z11-1.php'>Задание 1</a>";
				die("Error: not read or no exist.");
			}
			$file_array=file($file_name);

			echo "<table border='1' cellpadding='10'>";
			$find_patern="/(?<=\|)\s*(.*?)\s*(?=\|)/";
			$find_mail_patern="/(\w+@\w+.\w+)+/";
			$replace_patern="<a href='mailto:$0'>$0</a>";
			foreach($file_array as $elem){
				rtrim($elem," \n");
				$arr=[];
				echo "<tr>";
				preg_match_all($find_patern,$elem,$arr);
				foreach($arr[0] as $ell){
					$temp=$ell;
					if(preg_match($find_mail_patern,$temp)) $temp=preg_replace($find_mail_patern,$replace_patern,$temp);
					echo "<td>$temp</td>";
				}
				echo "</tr>";
			}
			echo "</table>";

			$mtime=filemtime($file_name);
			$ctime=filectime($file_name);
			echo "<p>Дата последней модификации: ".date("D d M Y g:i A",$mtime)."</p>";

			echo "<hr>";
			$info=$_SERVER["HTTP_USER_AGENT"];
			$browser_patern="/(Chrome|Firefox|Safari|Opera|MSIE|Edge)\/([\d.]+)/";
			$opers_patern="/(Windows|Linux|Android|iOS)\/?([\d.])*/";
			if(preg_match($browser_patern,$info,$arr)){
				echo "Браузер: $arr[1]<br>";
				if(isset($arr[2])) echo "Версия: $arr[2]<br>";
			}
			else echo "<p>Magick browser?</p>";
			echo "<br>";
			if(preg_match($opers_patern,$info,$arr)){
				echo "Операционная система: $arr[1]<br>";
				if(isset($arr[2])) echo "Версия: $arr[2]<br>";
			}
			else echo "<p>Magich os?</p>";
		?>
	</body>
</html>