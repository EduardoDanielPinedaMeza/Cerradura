<?php
include('bdESP.php'); 
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Tablas</title>

    <link rel="stylesheet" href="estilos.css">
</head>
<body>
    <div class="container">
        <table class="table">
            <caption>Mensajes de alerta</caption>
            <thead>
                <tr>
                    <th>Mensajes</th>
                    <th>Fechas y Horas</th>
                </tr>
            </thead>
            <tbody>
                <?php
                $consulta = $conexion->query("SELECT * FROM tmensajes");       
                while ($row = $consulta->fetch_array()) {
                    echo "<tr>";
                        echo "<td td data-label='Mensaje'> ".$row["Mensaje"]." </td>";
                        echo "<td td data-label='Fecha y hora'> ".$row["TiempoActual"]." </td>";
                    echo "</tr>";
                }
                ?>
            </tbody>
        </table>
    </div>
</body>
</html>