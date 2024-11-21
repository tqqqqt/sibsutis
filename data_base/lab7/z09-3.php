<html>
	<head><title>Show table</title></head>
	<body>
		<?php
			try{
				$conn=mysqli_connect("localhost","root","");
				mysqli_select_db($conn,"sample");
				$result=mysqli_query($conn,"select * from notebook_br4;");
				echo "<p>Таблица:</p>";
				echo "<table border='1' cellpadding='0px'>";
				echo "<tr>";
				echo "<td width='14px' height='15px' size=1>id</td>";
				echo "<td width='14px' height='15px' size=1>Имя</td>";
				echo "<td width='14px' height='15px' size=1>Город</td>";
				echo "<td width='14px' height='15px' size=1>Адрес</td>";
				echo "<td width='14px' height='15px' size=1>День рождения</td>";
				echo "<td width='14px' height='15px' size=1>Почта</td>";
				echo "</tr>";
				while($row=mysqli_fetch_row($result)){
					echo "<tr>";
					foreach($row as $elem) echo "<td width='14px' height='15px' size=1>$elem</td>";
					echo "</tr>";
				}
				echo "</table>";
				mysqli_close($conn);
			}
			catch(mysqli_sql_exception $exp){
				die("Ошибка: ".$exp->getMessage());
			}

			echo "<a href='z09-2.php'>Добавить элементы<br></a>";
			echo "<a href='z09-4.php'>Изменить существующие элементы</a>";
		?>
	</body>
</html>