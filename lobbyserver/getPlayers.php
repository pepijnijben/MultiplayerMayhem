<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 


$sql = "SELECT * FROM players";

$result = $conn->query($sql);
$results = array();


if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo $row["name"]. ";" . $row["room_id"]. ";" . $row["ip"]. ";" . $row["port"]. ";";
    }
} else {
    echo "";
}

mysql_close($conn);