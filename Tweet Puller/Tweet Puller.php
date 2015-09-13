<?php
/*
	Title: Tweet Puller
	Authors:	Lasha Zakariashvili
				Claudia Bergeron

	Description: Pull tweets from the Twitter Stream API. 
	
	Usage: N/A
	
	Notes:	- This is a work-in-progress! Currently very poor documentation!
*/
require_once('phirehose/Phirehose.php');
require_once('phirehose/OauthPhirehose.php');

/* -=-V-=-V-=-V-=-V-=-=- Twitter Keys go here -=-=-V-=-V-=-V-=-V-=- */
/*								    */
/* 	    	    "Twitter Keys (encrypted).txt"   		    */
/*		    Note: Won't work without them.   		    */
/*								    */
/* -=-^-=-^-=-^-=-^-=-=- Twitter Keys go here -=-=-^-=-^-=-^-=-^-=- */

		
$myfile = fopen("newfile.txt", "w") or die("Unable to open file!");

class SampleConsumer extends OauthPhirehose {
  public function enqueueStatus($status) {
    $data = json_decode($status, true);
    if (is_array($data) && isset($data['user']['screen_name'])) {
		$myfile = fopen("newfile.txt", "a") or die("Unable to open file!");
		fwrite($myfile, $data['user']['screen_name'] . ':' . urldecode($data['text']) . "\n");
		fclose($myfile);
    }
  }
}
// The OAuth credentials you received when registering your app at Twitter
define("TWITTER_CONSUMER_KEY", $keys['consumer_key']);
define("TWITTER_CONSUMER_SECRET", $keys['consumer_secret']);
// The OAuth data for the twitter account
define("OAUTH_TOKEN", $keys['access_token']);
define("OAUTH_SECRET", $keys['access_token_secret']);
// Start streaming
$sc = new SampleConsumer(OAUTH_TOKEN, OAUTH_SECRET, Phirehose::METHOD_SAMPLE);
$sc->consume();
fclose($myfile);
?>
