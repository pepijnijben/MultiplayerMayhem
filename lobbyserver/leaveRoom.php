<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

if (!$_POST['id'] )
{
	die("Please provide id");
}

$id = $_POST['id'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "UPDATE players SET room_id='-1' WHERE id=".$id;

if ($conn->query($sql) === TRUE) {
    echo $roomId;
} else {
    die("Error: " . $sql . "<br>" . $conn->error);
}