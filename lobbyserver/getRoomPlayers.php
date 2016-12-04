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

$sql = "SELECT * FROM rooms WHERE id=".$roomId;
$hostId = -1;

$result = $conn->query($sql);
if ($result->num_rows > 0)
{
	$data = $result->fetch_assoc();
	$hostId = $data['owner'];
}
if ($hostId == -1)
	die("");

$sql = "SELECT * FROM players WHERE room_id=".$roomId;

$result = $conn->query($sql);
$results = array();


if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
		if ($row['id'] == $hostId)
			echo $row["name"]. ";" . $row["room_id"]. ";" . $row["ip"]. ";" . $row["port"]. ";";
		else
			$results[] = $row;
	}
} else {
    echo "";
}

foreach ($results as $row)
{
	echo $row["name"]. ";" . $row["room_id"]. ";" . $row["ip"]. ";" . $row["port"]. ";";
}

mysql_close($conn);