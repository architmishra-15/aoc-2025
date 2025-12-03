import std.stdio;
import std.conv;
import std.string;
import std.array : array;
import std.bigint;

int solutionBrute(string s)
{
    if (s.length < 2)
        return 0;
    int best = -1;
    char bu = '0', bl = '0';
    foreach (i; 0 .. (s.length) - 1)
    {
        foreach (j; i + 1 .. s.length)
        {
            int v = (s[i] - '0') * 10 + (s[j] - '0');
            if (v > best)
            {
                best = v;
                bu = s[i];
                bl = s[j];
            }
        }
    }
    return best;
}

long solution(string str)
{
    string result = "";
    int start = 0;

    for (int i = 0; i < 12; ++i)
    {
        char maxChar = '0';
        int maxPos = start;

        // We need (k - i - 1) more digits after this one
        int remainingNeeded = 12 - i - 1;

        // Search from start to the position that leaves enough digits
        int searchEnd = cast(int) str.length - remainingNeeded;

        for (int j = start; j < searchEnd; ++j)
        {
            if (str[j] > maxChar)
            {
                maxChar = str[j];
                maxPos = j;
            }
        }

        result ~= maxChar;
        start = maxPos + 1; // Next search starts after this position
    }

    writefln("%s -> %s", str, result);
    return to!long(result);
}

void main()
{
    long answer = 0;
    auto f = File("input.txt", "r");

    string buf;

    f.readf("%s", buf);

    auto battries = buf.lineSplitter();

    foreach (battry; battries)
    {
        // Answer for first part.
        // answer += solutionBrute(battry);
        answer += solution(battry);
    }

    writeln(answer);
}
