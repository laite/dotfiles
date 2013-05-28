<?php
for ($i = 0; $i != 7; ++$i)
{
	if (isset($_COOKIE["kieli$i"]))
	{
		$index = "kieli$i";
		echo "$_COOKIE[$index] <br>";
	}
	else
		break;
}
?>
