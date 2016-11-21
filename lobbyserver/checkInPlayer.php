<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

if (!$_POST['name'])
{
	die("Please provide name");
}

$name = $_POST['name'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 


$sql = "UPDATE players SET last_update='".date("Y-m-d H:i:s")."' WHERE name=".$name;

if ($conn->query($sql) === TRUE) {
    echo "$name successfully checked in";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

mysql_close($conn);