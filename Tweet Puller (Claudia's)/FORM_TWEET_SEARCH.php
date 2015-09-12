
<html>
<body>
<br/>
<table>
<td>
<tr>
Enter username:
</tr>
<tr>
<form name="user/number" method="post" action="littleAPI.php">
<input type="text" name="user" value="<?php if (isset($_POST['user'])) echo $_POST['user']; ?>">
</tr>
</td>
<td>      </td>
<td>
<tr>
Enter number of tweets to test:
</tr>
<tr>
<input type="text" name="number" value="<?php if (isset($_POST['number'])) echo $_POST['number']; ?>">&nbsp;
<input type="submit" name="submit" value="GO"/>
</tr>
</td>
<td>

<br></td>
</table>
</form>
</html>