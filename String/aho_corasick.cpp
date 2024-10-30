// Aho corasic for all pattern search in a text



        vector<map<char, int>> nxtCh;  // Trie transitions

        vector<int> fail, nxtWord, wordId;  // Fail function, next word transition, word IDs


        int addNode()
        {
                nxtCh.emplace_back();
                fail.push_back(0);
                nxtWord.push_back(0);
                wordId.push_back(-1);
                return wordId.size() - 1;  // Return new node's index
        }

        int insert(const string &s, int idx)
        {
                int cur = 0;
                for (char c : s)
                {
                        if (!nxtCh[cur].count(c))
                        {
                                int to = addNode();  // Create a new node if transition doesn't exist
                                nxtCh[cur][c] = to;
                        }
                        cur = nxtCh[cur][c];  // Move to the next node
                }
                if (wordId[cur] == -1)
                {
                        wordId[cur] = idx;  // Assign word index to the current node
                }
                return wordId[cur];
        }

        void computeFailure()
        {
                queue<int> q;

                for (auto &it : nxtCh[0])
                {
                        q.push(it.second);
                }
                while (!q.empty())
                {
                        int u = q.front();
                        q.pop();

                        for (auto [c, v] : nxtCh[u])
                        {
                                int f = fail[u];  // Get the fail value for the current node

                                while (nxtCh[f].find(c) == nxtCh[f].end() && f != 0)
                                {
                                        f = fail[f];
                                }

                                fail[v] = nxtCh[f][c];  // Set the fail value for the next node
                                nxtWord[v] = wordId[fail[v]] != -1 ? fail[v] : nxtWord[fail[v]];
                                q.push(v);
                        }
                }
        }

        vector<vector<int>> match(const string &s, int q)
        {
                vector<vector<int>> ret(q);  // Store pattern occurrences
                int cur = 0;

                for (int i = 0; i < s.size(); i++)
                {
                        char c = s[i];

                        while (nxtCh[cur].find(c) == nxtCh[cur].end() && cur != 0)
                        {
                                cur = fail[cur];
                        }

                        cur = nxtCh[cur][c];
                        int u = cur;

                        while (u != 0)
                        {
                                if (wordId[u] != -1)
                                {
                                        ret[wordId[u]].push_back(i);
                                }
                                u = nxtWord[u];
                        }
                }
                return ret;
        }

        string txt;


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        string text;
        cin>>text;
        int n;
        cin>>n;

        vector<int>id;

        addNode();

        for(int i=0;i<n;i++)
        {
                string s;
                cin>>s;
                id.push_back(insert(s,i));
        }

        computeFailure();


        auto matching = match(text,n);


        for(int i=0;i<n;i++)
        {
                cout<<"YN"[matching[id[i]].empty()]<<endl;
        }

        return 0;




}