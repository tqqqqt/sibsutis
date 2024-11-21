<html>
	<body>
		<?php
			//num1
			$size=333;
			$color="red";
			echo "<font size='$size' color='$color'>Hello world!</font>";
			echo "<hr>";

			//num2
			$var1="Alice";
			$var2="My friend is $var1";
			$var3='My friend is $var1';
			$var4=& $var1;
			echo "<p>Var1=$var1</p>";
			echo "<p>Var2=$var2</p>";
			echo "<p>Var3=$var3</p>";
			echo "<p>Var4=$var4</p>";
			$var1="Bob";
			echo "<p>Var1=$var1</p>";
			echo "<p>Var2=$var2</p>";
			echo "<p>Var3=$var3</p>";
			echo "<p>Var4=$var4</p>";

			$user="Michael";
			$$user="Jackson";
			echo "<p>\$user=$user</p>";
			echo "<p>\$\$user=";
			echo $$user;
			echo "</p>";
			echo "<hr>";

			//num3
			$e=2.718281;
			echo "<p>Число Эейлера равно $e</p>";
			$temp=(string) $e;
			echo "<p>";
			echo gettype($temp);
			echo " -> $temp</p>";
			$temp=(int) $e;
			echo "<p>";
			echo gettype($temp);
			echo " -> $temp</p>";
			$temp=(bool) $e;
			echo "<p>";
			echo gettype($temp);
			echo " -> $temp</p>";
			echo "<hr>";

			//num4
			$p=-9999;
			if(isset($_GET["p"])){
				$p=$_GET["p"];
			}
			switch ($p) {
				case -5:
					echo "<p>П равен минус пять</p>";
					break;
				case -4:
					echo "<p>П равен минус четыре</p>";
					break;
				case -3:
					echo "<p>П равен минус три</p>";
					break;
				case -2:
					echo "<p>П равен минус два</p>";
					break;
				case -1:
					echo "<p>П равен минус один</p>";
					break;
				case 0:
					echo "<p>П равен ноль</p>";
					break;
				case 1:
					echo "<p>П равен один</p>";
					break;
				case 2:
					echo "<p>П равен два</p>";
					break;
				default:
					echo "<p>Error: -5<=p<=2";
					break;
			}
			echo "<hr>";

			//num5
			$color_2="blue";
			$rows=-1;
			echo "<table border='1' cellpadding='5px'>";
			while($rows++<9){
				echo "<tr>";
				$cols=-1;
				while($cols++<9){
					$temp=($rows+1)*($cols+1);
					if($rows==$cols) echo "<td bgcolor='$color_2'>$temp</td>";
					else echo "<td>$temp</td>";
				}
				echo "</tr>";
			}
			echo "</table>";
		?>
	</body>
</html>
