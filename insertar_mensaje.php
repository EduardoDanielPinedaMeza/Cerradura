<?php 
include("bdESP.php");

date_default_timezone_set('America/Mexico_City');
$_GET["Tiempo"]=date("Y-m-d H:i:s");

if(isset($_GET["Nombre"])) {
$nombre = $_GET["Nombre"];
$conexion->query("INSERT INTO tmensajes(Mensaje, TiempoActual) 
    VALUES(
        '".$_GET["Nombre"]."',
        '".$_GET["Tiempo"]."'
    )");
echo "HOLAAAAAAAAAAAAAA";

$para = 'mazethekillerpro@gmail.com';
$asunto = "ALERTA";
$descripcion = 'Estan intentando abrir la cerradura | Tiempo: ['.$_GET["Tiempo"].']';
$de = 'From: kratospartx@gmail.com';

if (mail($para, $asunto, $descripcion, $de))
   {
}
?>
<script type="text/javascript">
   alert("Se enviaron tus datos al correo electronico");
   window.location= 'index.php';
</script>
<?php
}else{   
echo "errorrrr";
}
?>