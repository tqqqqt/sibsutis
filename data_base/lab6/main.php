<html>
	<body>
		<?php
			//1
			//1.1
			$treug=[];
			for($i=1;$i<11;$i++) $treug[$i-1]=$i*($i+1)/2;
			for($i=0;$i<count($treug);$i++) echo "$treug[$i]  ";
			echo "<p></p>";
			//1.2
			$kyd=[];
			for($i=1;$i<11;$i++) $kyd[$i-1]=$i*$i;
			for($i=0;$i<count($kyd);$i++) echo "$kyd[$i]  ";
			echo "<p></p>";
			//1.3
			$rez=array_merge($treug,$kyd);
			for($i=0;$i<count($rez);$i++) echo "$rez[$i]  ";
			echo "<p></p>";
			//1.4
			sort($rez);
			for($i=0;$i<count($rez);$i++) echo "$rez[$i]  ";
			echo "<p></p>";
			//1.5
			unset($rez[0]);
			foreach($rez as $elem) echo "$elem  ";
			echo "<p></p>";
			//1.6
			$rez1=array_unique($rez);
			foreach($rez1 as $elem) echo "$elem  ";
			echo "<p></p>";
			echo "<hr>";

			//2
			$color="blue";
			echo "<table border='1' cellpadding='0px'>";
			for($i=1;$i<31;$i++){
				echo "<tr>";
				for($j=1;$j<31;$j++){
					$temp=$i*$j;
					$ttemp=$temp%7;
					if($ttemp==0) $color="white";
					elseif($ttemp==1) $color="aqua";
					elseif($ttemp==2) $color="blue";
					elseif($ttemp==3) $color="yelow";
					elseif($ttemp==4) $color="purple";
					elseif($ttemp==5) $color="red";
					elseif($ttemp==6) $color="lime";
					echo "<td bgcolor='$color' width='14px' height='15px' size=1>&nbsp</td>";
				}
				echo "</tr>";
			}
			echo "</table>";
			echo "<hr>";

			//3
			//3.1
			$cust=["cnum"=>2001, "cname"=>"Hoffman", "city"=>"London", "snum"=>1001, "rating"=>100];
			foreach($cust as $key=>$val) echo "<p>$key = $val</p>";
			echo "<p>--</p>";
			//3.2
			ksort($cust);
			foreach($cust as $key=>$val) echo "<p>$key = $val</p>";
			echo "<p>--</p>";
			//3.3
			asort($cust);
			foreach($cust as $key=>$val) echo "<p>$key = $val</p>";
			echo "<p>--</p>";
			//3.4
			sort($cust); // don't save connect keys with value
			foreach($cust as $key=>$val) echo "<p>$key = $val</p>";
			echo "<p>--</p>";
			echo "<hr>";

			//4
			$alig="left";
			$valig="top";
			if(isset($_POST["alig"])) $alig=$_POST["alig"];
			if(isset($_POST["valig"])) $valig=$_POST["valig"];
			echo "<table border='1px'><tr><td width='300px' height='300px' align='$alig' valign='$valig'>HelloWorld</td></tr></table>";
		?>
		<form method="post" action="main.php">
			<p>Align:</p>
			<input type="radio" name="alig" value="left">Left
			<input type="radio" name="alig" value="center">Center
			<input type="radio" name="alig" value="right">Right
			<p>VAlign:</p>
			<input type="checkbox" name="valig" value="top">Top
			<input type="checkbox" name="valig" value="midle">Midle
			<input type="checkbox" name="valig" value="bottom">Bottom
			<p></p>
			<input type="submit" value="Выполнить">
		</form>
	</body>
</html>
