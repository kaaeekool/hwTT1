#include "trendtracker.h"

using namespace std;

Trendtracker::Trendtracker()
{
	//no hashtags
	E.clear;
}

void Trendtracker::insert(string ht)
{
	Entry h;
	h.pop = 0;
	for (int i = 0; i < E.size(); i++)
	{
		//check if # is in the vector
		if (E[i].hashtag == ht)
			return;
	}
	h.hashtag = ht;
	E.push_back(h);

}

int Trendtracker::size()
{
	return E.size();
}

void Trendtracker::tweeted(string ht)
{
	for (int i = 0; i < E.size(); i++)
	{
		if (E[i].hashtag == ht)
			E[i].pop++ //Adds 1 to the tweeted times
	}
}

int Trendtracker::popularity(string name)
{
	for (int i = 0; i < E.size(); i++) //looking for hashtag
	{
		if (E[i].hashtag == name)
			return E[i].pop; //returns tweeted time of hashtag
	}
}

string Trendtracker::top_trend()
{
	string most;

	if (E.size() == 0)
	{
		return "";
	}
		
	else
	{
		for (int i = 0; i < E.size(); i++)
		{
			if (i + 1 < E.size() && E[i].pop > E[i + 1].pop)
			{
				swap(E[1], E[i + 1]);
			}
			else
				most = E[i].hashtag;
		}
	}
	return most;
}

void Trendtracker::top_three_trends(vector<string>& T)
{
	int top = 0;
	T.clear(); //empty vector

	if (E.size() == 0)
		return;

	//top 1 trend
	else if (E.size() == 1)
		T.push_back(E.back().hashtag);

	//top 2 trend
	else if (E.size() == 2)
	{
		if (E.back().pop < E.front().pop)
		{
			swap(E.back(), E, front());
			T.push_back(E.back().hashtag);
			T.push_back(E.front().hashtag);
		}
	}

	//top 3 trend
	else
	{
		for (int i = 0; i < E.size() && top != 3; i++)
		{
			if (i + 1 < E.size() && E[i].pop > E[i + 1].pop)
				swap(E[i], E[i + 1]);

			if (i == E.size() - 1)
			{
				top++;
				i = i - 1;
			}
		}
		T.push_back(E.back().hashtag);
		T.push_back(E[E.size() - 2].hashtag);
		T.push_back(E[E.size() - 3].hashtag);
	}
}

void Trendtracker::remove(string ht)
{
	int cancelled;
	for (int i = 0; i < E.size(); i++)
	{
		if (E[i].hashtag == ht)
			cancelled = i;
	}
	E.erase(E.begin() + cancelled);
}

void Trendtracker::top_k_trends(vector<string>& T, int k)
{
	T.clear();
	for (int i = 0; i < k; i++) //number of hastags inside vector
	{
		for (int j = 0; j < E.size(); j++)
		{
			if (j + 1 < E.size() && E[i].pop > E[i + 1].pop)
				swap(E[i], E[i + 1]);
		}
		T.push_back(E[E.size() - 1 - i].hashtag);
	}
}