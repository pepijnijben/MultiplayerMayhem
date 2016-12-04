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

$sql = "UPDATE rooms SET last_update='".date("Y-m-d H:i:s")."' WHERE owner=".$id;
$conn->query($sql);

$sql = "UPDATE players SET last_update='".date("Y-m-d H:i:s")."' WHERE id=".$id;

if ($conn->query($sql) === TRUE) {
    echo "$id successfully checked in";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}