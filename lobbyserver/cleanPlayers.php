<?php

$date = date("Y-m-d H:i:ss");
$timestamp = time() + 50;

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


while ($timestamp > time())
{
	// Keep cleaning players
	$sql = "SELECT * FROM players";
	$result = $conn->query($sql);
	$results = array();
	
	
	if ($result->num_rows > 0) {
		while($row = $result->fetch_assoc()) {
			if (time() - 10 > strtotime($row['last_update']))
			{
				$results[] = $row['id'];
			}
		}
	}
	
	foreach ($results as $id)
	{
		$sql = "DELETE FROM players WHERE id=".$id;
		$conn->query($sql);
	}
	
	// Make sure its only called every 5 seconds
	sleep(5);
}