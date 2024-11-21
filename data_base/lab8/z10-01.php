<html>
	<head><title>Main page</title>
	</head>
	<body>
		<?php
			try{
				$conn=mysqli_connect("localhost","root","");
				mysqli_select_db($conn,"sample");
				$result=mysqli_query($conn,"show tables;");
				$add_to_url="";
				$count_tables=0;
				$tables=[];
				while($row=mysqli_fetch_row($result)){
					if(strlen($add_to_url)>0) $add_to_url.="&".("t".$count_tables)."=".$row[0];
					else $add_to_url.=("t".$count_tables)."=".$row[0];
					array_push($tables,$row[0]);
					$count_tables+=1;
				}
				echo "<form action='z10-2.php?$add_to_url' method='post'>";
				echo "<table>";
				echo "<tr>";
				echo "<td width='96px' size=1>таблицы</td>";
				echo "<td width='96px' colspan='2' align='center'><b>отобразить</td>";
				echo "</tr>";
				echo "<tr>";
				echo "<td></td>";
				echo "<td width='120px' size=1><b>структуру</td>";
				echo "<td width='120px' size=1><b>содержимое</td>";
				echo "</tr>";
				$curent_table=0;
				foreach($tables as $elem){
					echo "<tr>";
					echo "<td><b>$elem</b></td>";
					echo "<td><input type=checkbox name='structure$curent_table' value='1'></td>";
					echo "<td><input type=checkbox name='content$curent_table' value='1'></td>";
					echo "</tr>";
					$curent_table++;
				}
				echo "</table>";
				echo "<input type=hidden name='count_tab' value=$count_tables>";
				echo "<input type=submit value='Вывести'>";
				echo "</form>";
				mysqli_close($conn);
			}
			catch(mysqli_sql_exception $exp){
				die("Error: ".$exp);
			}
		?>
	</body>
</html>