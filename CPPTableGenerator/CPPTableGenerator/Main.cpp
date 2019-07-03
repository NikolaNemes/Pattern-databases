#include <iostream>
#include "SixSixThreePartition.h"

using namespace std;

int main()
{
	cout << "This program generates the three tables needed for the 663 partition table" << endl;
	cout << "Generating partition 1 (size 6)" << endl;
	Partition1::create_partition_inplace();
	cout << "Generating partition 2 (size 6)" << endl;
	Partition2::create_partition_inplace();
	cout << "Generating partition 3 (size 6)" << endl;
	Partition3::create_partition_inplace();
}