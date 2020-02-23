# ADA-stable-matching
GS algorithm

Valentine's Day
It is Valentine's Day! Since there are still n single boys and n single girls in VCN research center, they want to match themselves to celebrate the Valentine's Day. Note that, the match should be stable, and in VCN research center, only boys can propose to girls.

Input
The first line of the input contains one single integers n (1≤n≤1000).

Then following n lines. Each line contains n+1 strings, which the first string indicates the boy's name, and the next n names describe the prefer list of that boy(who he prefers appears first).

Then following n lines describe the same information for n girls.

Output
Output n lines. Each line contains two names for a couple, and the boy's name comes first.

All boys' names should follow the same order as the input.

If there is no stable matching exist, please output only one single word 'impossible'(without quote).

Sample input
3
Lan Stephan Hong Dogbean
Yee Dogbean Hong Stephan
David Stephan Dogbean Hong
Stephan David Lan Yee
Dogbean Lan David Yee
Hong Yee Lan David

Sample output
Lan Hong
Yee Dogbean
David Stephan
