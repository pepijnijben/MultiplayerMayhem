<?php

$servername = "localhost";
$username = "admin";
$password = "pass";
$dbname = "multiplayer_mayhem";

if (!$_POST['id'])
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

$sql = "INSERT INTO rooms (name, owner, last_update)
VALUES ('Room', '".$id."', '".date("Y-m-d H:i:s")."')";

if ($conn->query($sql) === TRUE) {
	$last_id = $conn->insert_id;
    echo $last_id;
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}