<h3>This repository involves Problem Set 3 Week 3 from the course CS50’s Introduction to Computer Science</h3>

Each folder contains different solutions to a set of given problems.

<h1>"plurality.c" inside folder "plurality": Plurality</h1>

<h4><strong>Problem to Solve</strong></h4>

Elections come in all shapes and sizes. In the UK, the Prime Minister is officially appointed by the monarch, who generally chooses the leader of the political party that wins the most seats in the House of Commons. The United States uses a multi-step Electoral College process where citizens vote on how each state should allocate Electors who then elect the President.

Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”). In the plurality vote, every voter gets to vote for one candidate. At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

For this problem, you’ll implement a program that runs a plurality election.

Be sure to test your code to make sure it handles…

<ul>
  <li>An election with any number of candidate (up to the MAX of 9)</li>
<li>Voting for a candidate by name</li>
<li>Invalid votes for candidates who are not on the ballot</li>
<li>Printing the winner of the election if there is only one</li>
<li>Printing the winner of the election if there are multiple winners</li>
</ul>

<h1>"runoff.c" inside folder "runoff": Runoff</h1>

<h4><strong>Problem to Solve</strong></h4>

There’s another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference. The resulting ballots might therefore look like the below.

![image](https://github.com/user-attachments/assets/199261ab-9603-4c2c-b34c-8d67b66e1c62)

Here, each voter, in addition to specifying their first preference candidate, has also indicated their second and third choices. And now, what was previously a tied election could now have a winner. The race was originally tied between Alice and Bob, so Charlie was out of the running. But the voter who chose Charlie preferred Alice over Bob, so Alice could here be declared the winner.

Ranked choice voting can also solve yet another potential drawback of plurality voting. Take a look at the following ballots.

![image](https://github.com/user-attachments/assets/a6bed64e-90cb-44e1-bb6b-fa8998688ec6)

Who should win this election? In a plurality vote where each voter chooses their first preference only, Charlie wins this election with four votes compared to only three for Bob and two for Alice. But a majority of the voters (5 out of the 9) would be happier with either Alice or Bob instead of Charlie. By considering ranked preferences, a voting system may be able to choose a winner that better reflects the preferences of the voters.

One such ranked choice voting system is the instant runoff system. In an instant runoff election, voters can rank as many candidates as they wish. If any candidate has a majority (more than 50%) of the first preference votes, that candidate is declared the winner of the election.

If no candidate has more than 50% of the vote, then an “instant runoff” occurrs. The candidate who received the fewest number of votes is eliminated from the election, and anyone who originally chose that candidate as their first preference now has their second preference considered. Why do it this way? Effectively, this simulates what would have happened if the least popular candidate had not been in the election to begin with.

The process repeats: if no candidate has a majority of the votes, the last place candidate is eliminated, and anyone who voted for them will instead vote for their next preference (who hasn’t themselves already been eliminated). Once a candidate has a majority, that candidate is declared the winner.

Sounds a bit more complicated than a plurality vote, doesn’t it? But it arguably has the benefit of being an election system where the winner of the election more accurately represents the preferences of the voters. In a file called runoff.c in a folder called runoff, create a program to simulate a runoff election.

<h4><strong>How to test</strong></h4>

Be sure to test your code to make sure it handles:
<ul>
  <li>An election with any number of candidate (up to the MAX of 9)</li>
<li>Voting for a candidate by name</li>
<li>Invalid votes for candidates who are not on the ballot</li>
  <li>Printing the winner of the election if there is only one</li>
  <li>Not eliminating anyone in the case of a tie between all remaining candidates</li>
</ul>
