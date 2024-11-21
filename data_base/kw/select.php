<html>
	<head><title>Main page</title></head>
	<body>
		<?php
			include("connect.inc");
			$result=mysqli_query($conn,"show tables;");
			$tables=[];
			while($row=mysqli_fetch_row($result)) array_push($tables,$row[0]);

			echo "<table border='1' cellpadding='10'>";
			echo "<tr>";
			echo "<td>Просмотреть содержание</td>";
			echo "<td>Добавить запись</td>";
			echo "</tr>";
			foreach($tables as $elem){
				echo "<tr>";
				echo "<td><a href='view.php?table=$elem' target='display'>$elem</a></td>";
				echo "<td><a href='add.php?table=$elem' target='display'>$elem</a></td>";
				echo "</tr>";
			}
			echo "</table>";

			echo "<a href='quest.php?target=z1' target='display'><p>Самые популярные салоны</p></a>";
			echo "<a href='quest.php?target=z2' target='display'><p>Количество заказов мастеров</p></a>";
			echo "<a href='quest.php?target=z3' target='display'><p>Работающие мастера по датам</p></a>";

			include("close.inc");
		?>
	</body>
</html>