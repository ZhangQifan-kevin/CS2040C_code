#include <bits/stdc++.h>
using namespace std;

template<typename T1, typename T2>
class table{
private:
	int total_number;
	int table_size;
	vector<tuple<T1,T2, int>> hash_table;
	vector<bool> is_empty;

	pair<int,int> find(T1 key){
		int index1 = -1;
		int index2 = hash<T1>{}(key) % table_size;
		while(get<2>(hash_table[index2]) != -1 && get<0>(hash_table[index2]) != key){
			index1 = index2;
			index2 = get<2>(hash_table[index2]);
		}
		if(get<0>(hash_table[index2]) == key) {return {index1, index2};}
		else {
			return {-1,-1};
		}
	}
public:
	table() {
		total_number = 0;
		table_size = 997;
		hash_table.assign(table_size, {T1(),T2(),-1});
		is_empty.assign(table_size, true);
	}
	table(int size) {
		total_number = 0;
		table_size = size; // Find the nearest prime number
		hash_table.assign(table_size, {T1(),T2(),-1});
		is_empty.assign(table_size, true);
	}

	~table() {}

	void insert(pair<T1, T2> key_value){	
		auto& [key, value] = key_value;
		if(find(key).second == -1) {
			int index = hash<T1>{}(key) % table_size;
			bool no_collision = true;
			while(get<2>(hash_table[index]) != -1) {
				no_collision = false;
				index = get<2>(hash_table[index]);
			}
			if(no_collision) {
				get<0>(hash_table[index]) = key;
				get<1>(hash_table[index]) = value;
				is_empty[index] = false;
			}
			else{
				int i;
				for(i = table_size - 1; !is_empty[i] && i >= 0; i--);
				is_empty[i] = false;
				get<2>(hash_table[index]) = i;
				get<1>(hash_table[index]) = value;
		    	get<0>(hash_table[index]) = key;
 			}
 			total_number++;
 		}
 		else{
 			get<1>(hash_table[find(key).second]) = value;
 		}
	}

	T2 search(T1 key){
		auto [index1, index2] = find(key);
		if(index2 == -1){
			cout << "The key " << key << " does not exist in the table.\n";
			return T2();
		}
		else{
			return get<1>(hash_table[index2]);
		}
	}


	void erase(T1 key){
		auto [index1, index2] = find(key);
		if(index2 == -1) return;
		else{
			if(index1 == -1){
				hash_table[index2] = {T1(),T2(),-1};
				is_empty[index2] = true;
			}
			else{
				get<2>(hash_table[index1]) = get<2>(hash_table[index2]);
				hash_table[index2] = {T1(),T2(),-1};
				is_empty[index2] = true;
			}
		}
		total_number--;
	}

	void print(){
		for(int i = 0; i < table_size; ++i){
			if(!is_empty[i])
				cout << "Key : " << get<0>(hash_table[i]) << " Value : " << get<1>(hash_table[i]) << "\n";
		}
	}
};
int main()
{
	table<string,int> Mytable(10);
	Mytable.insert({"Steven",20});
	Mytable.print();
	Mytable.erase("Steven");
	cout << Mytable.search("Steven") << "\n";
	return 0;
}
