<html>
<body>

<H1> How'd You Fare? </H1>

<?php
	$guess = $_POST["guess"];
	$flag = 0;

	$num=array (rand (0,20), rand (0,20), rand (0,20), rand (0,20), rand (0,20));

	echo $num[0], " ", $num[1], " ", $num[2], " ", $num[3], " ", $num[4];
?>
</br>
<?php
	for ($i=0; $i<5; $i++)
		if ($guess==$num[$i])
			$flag=1;

	if ($flag==1)
		echo "You Got It!";
	else
		echo "Wrong!";
?>

<form method="POST" action="Lab3Main.php">
	<input type="submit" value="Try Again" />
</form>

</body>
</hmtl>
