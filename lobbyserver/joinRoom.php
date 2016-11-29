<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

if (!$_POST['roomId'] || !$_POST['id'] )
{
	die("Please provide roomId and id");
}

$roomId = $_POST['roomId'];
$id = $_POST['id'];



// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "UPDATE players SET room_id='".$roomId."' WHERE id=".$id;

if ($conn->query($sql) === TRUE) {
    echo $roomId;
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

mysql_close($conn);