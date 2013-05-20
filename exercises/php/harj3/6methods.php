<?php

/**
 * Palauttaa taulukon suurimman arvon
 *
 * @param array $taulu sisältää luvut, joista maksimi etsitään
 * @return int suurin arvo tai -1 virheen sattuessa
 */
function own_max($taulu)
{
	if ((!is_array($taulu)) || (count($taulu) == 0))
		return -1;

	$max = $taulu[0];
	foreach ($taulu as $key => $value)
	{
		if ($value > $max)
			$max = $value;
	}

	return $max;
}

/**
 * Palauttaa taulukon pienimmän arvon
 *
 * @param array $taulu sisältää luvut, joista minimi etsitään
 * @return int pienin arvo tai -1 virheen sattuessa
 */
function own_min($taulu)
{
	if ((!is_array($taulu)) || (count($taulu) == 0))
		return -1;

	$min = $taulu[0];
	foreach ($taulu as $key => $value)
	{
		if ($value < $min)
			$min = $value;
	}

	return $min;
}

/**
 * Palauttaa taulukon lukujen keskiarvon
 *
 * @param array $taulu sisältää luvut, joista keskiarvo lasketaan
 * @return int|float keskiarvo tai -1 virheen sattuessa
 */
function own_avg($taulu)
{
	if ((!is_array($taulu)) || (count($taulu) == 0))
		return -1;

	$summa = array_sum($taulu);
	$maara = count($taulu);

	// $maara ei voi olla 0, sillä testasimme sen jo funktion alussa
	return ($summa/$maara);
}

?>
