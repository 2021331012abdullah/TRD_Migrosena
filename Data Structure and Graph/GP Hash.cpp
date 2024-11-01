struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
x
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
}; //For long long int to long long int
typedef gp_hash_table<int, int, custom_hash>table;

//example
struct chash {
    int operator()(pair<int, int> x) const { return x.first * 31 + x.second; }
};
gp_hash_table<pair<int, int>, int, chash> table;