<?php 
session_start();
// estetään editoiminen ilman haettua sivua
$_SESSION['current_page'] = null;
?>
<html>
	<head>
		<title>Inplace - editointia</title>
		<!-- Ladataan jquery -->
		<script type="text/javascript" src="jquery-1.10.1.js"></script>
		<!-- Ladataan jeditable -->
		<script type="text/javascript" src="jeditable.js"></script>
		<!--otetaan käyttöön prototype.js-->
		<script type="text/javascript" src="prototype.js"></script>
		<!--otetaan käyttöön pt_kaytto.js jolla käytetään prototype.js:n funktioita-->
		<script type="text/javascript" src="pt_kaytto.js"></script>
	</head>

	<script>
		// käytämme jQuery:ä $:n sijaan, sillä prototype/jquery ovat konfliktissa muuten
		jQuery(document).ready(function() {
			jQuery('#page_area').editable('tallenna.php', {
				type	: 'textarea',
				cancel	: 'peruuta',
				submit	: 'tallenna',
				tooltip : 'Editoi minua!'
			});
		});
	</script>
	<body>
		<p>
			Hae sivujen otsikoista:<br />
			<input type="text" name="hakusana" id="hakusana" size="20" onchange="updatePage()" >
		</p>
		<p id="page_area">
			Kirjoita hakukenttään sivun otsake, tai jotakin sinne päin.
		</p>
		<div id="footer">
			<span style='color:#888; font-size:8pt;'>
				Voit editoida ylläolevaa tekstiä klikkaamalla sitä!
			</span>
		</div>
	</form>
</body>
</html>
