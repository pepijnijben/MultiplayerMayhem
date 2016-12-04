<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

if (!$_POST['roomId'])
{
	die("Please provide roomId");
}

$roomId = $_POST['roomId'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "DELETE FROM rooms WHERE id=".$roomId;

if ($conn->query($sql) === TRUE) {
	echo "1";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}