<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

if (!$_POST['name'] && !$_POST['port'])
{
	die("Please provide name and port");
}

$name = $_POST['name'];
$port = $_POST['port'];



// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 


$sql = "INSERT INTO players (name, ip, port, last_update)
VALUES ('".$name."', '".$_SERVER['REMOTE_ADDR']."', '".$name."', '".date("Y-m-d H:i:s")."')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

mysql_close($conn);