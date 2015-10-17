<?php
/*
	Title: Tweet Puller
	Author:	Lasha Zakariashvili
				
	Credits:	fennb (https://github.com/fennb/phirehose)

	Description: Pull tweets from the Twitter Stream API using the Phirehose library 
		(created by fennb). This will help analyze Twitter activity and in the future
		classify the content twitter users publish. For more information on the overall
		scope of this project, check out https://github.com/Lzak/stcawn .
	
	Usage:	1) Define Keys:		You must first define the Twitter Keys (see "OAuth for Twitter")
			2) Create class:	$var = new TweetPuller(duration_in_seconds);
			3) Call consume():	$var->consume();
	
	Notes:	- ONLY ENGLISH TWEETS ARE DISPLAYED! To remove this restriction, simply delete
				"&& $data['lang'] == "en"" from enqueueStatus($status).
			- Tweets are put into a file called "Tweets.txt"
			- The text format is as so:
				>>>	<user>:TWITTER_NAME<tweet>:TWEET_MESSAGE<eo_tweet>\n
			- Keep in mind, people tend to post tweets with more than 1 line, which might
				make the Twitter.txt file look messy. When processing tweets, make use of
				of the <user>, <tweet> and <eo_tweet>. 
			- ALSO, Twitter users post tweets in different languages. A good addition to this
				would be to translate some of the languages.
*/
require_once('phirehose/Phirehose.php');
require_once('phirehose/OauthPhirehose.php');

// OAuth for Twitter
define("TWITTER_CONSUMER_KEY", "XXXXXXXXXXXXXXXXXXXXXXXX");
define("TWITTER_CONSUMER_SECRET", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
define("OAUTH_TOKEN", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
define("OAUTH_SECRET", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

class TweetPuller extends OauthPhirehose {
	protected $fileStream;
	protected $time_start;
	protected $run_duration;	//How long you wish to pull tweets
	
	
	public function __construct($run_duration = 5) {
		$this->time_start = time();
		$this->run_duration = $run_duration;		//In seconds
		return parent::__construct(OAUTH_TOKEN, OAUTH_SECRET, Phirehose::METHOD_SAMPLE);
	}
	
	
	//This will return a handle to the file, which can then be used for fwrite()
	public function getFile() {
		$this->fileStream = fopen("Tweets.txt", "a") or die("Unable to open file!");
		return $this->fileStream;
	}
	
	//This will close the file. After every fwrite() there should be a closeFile() to follow
	public function closeFile() {
		fclose($this->fileStream);
	}
	
	//Required function for phirehose. Every tweet will run this function.
	public function enqueueStatus($status) {
		if (time() - $this->time_start < $this->run_duration) {
			$data = json_decode($status, true);
			if (is_array($data) && isset($data['user']['screen_name']) && isset($data['text'])) {
				//This will output =>    <user>:TwitterName<tweet>:MyTwitterMessage\n
				fwrite($this->getFile(), '<user>:' . $data['user']['screen_name'] . '<tweet>:' . urldecode($data['text']) . '<eo_tweet>' . "\n");
				$this->closeFile();
			}
		} else {
			$this->disconnect();
		}
	}
}

// Start streaming
echo "Initializing Tweet Puller...<br>";
$engine = new TweetPuller(5);
$engine->setLang("en");			//Only pull English tweets
echo "Tweet Puller started.<br>";
$engine->consume();				//Starts the tweet pull
echo "Tweet Pull complete.<br>";
?>