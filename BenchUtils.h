#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "TicToc.h"

typedef std::function<void()> f_pre_t;
typedef std::function<void()> f_pro_t;
typedef std::function<bool()> f_post_t;

class BenchUtils
{
	struct Test
	{
		string name;
		f_pre_t pre;
		f_pro_t process;
		f_post_t post;

		vector<int> times;

		Test(const string& name, const f_pre_t& pre, const f_pro_t& process, const f_post_t& post) : name(name), pre(pre), process(process), post(post) {}
	};

	map<string, Test> tests;
	f_pre_t commonPre = []() -> void {};

public:
	BenchUtils();
	~BenchUtils();

	void addTest(const string& name, const f_pre_t& pre, const f_pro_t& process, const f_post_t& post)
	{
		tests.insert(std::pair<string, Test>(name, Test(name, pre, process, post)));
	}
	void addTest(const string& name, const f_pro_t& process)
	{
		addTest(name, []() -> void {}, process, []() -> bool {true; });
	}

	void setCommonPre(f_pre_t commonPre)
	{
		this->commonPre = commonPre;
	}

	void runTests(int times)
	{
		for (int i = 0; i < times; i++)
		{
			commonPre();
			for (std::map<string, Test>::iterator it = tests.begin(); it != tests.end(); it++)
			{
				it->second.pre();

				TicToc t;
				t.tic();
				it->second.process();
				t.toc();
				it->second.times.push_back(t.getMillisRaw());

				if (!it->second.post())
				{
					cerr << "Error en test " << it->second.name << ", iteration " << i << endl;
				}
			}
		}
	}

};

