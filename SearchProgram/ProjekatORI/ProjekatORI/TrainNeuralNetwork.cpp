#include "NeuralNetwork.h"



void trainPartition3(int*** partition3)
{


	tiny_dnn::network<tiny_dnn::sequential> net;
	//net << tiny_dnn::fully_connected_layer(3, 10);
	//net << tiny_dnn::leaky_relu_layer();
	//net << tiny_dnn::fully_connected_layer(10, 3);
	//net << tiny_dnn::relu_layer();
	//net << tiny_dnn::fully_connected_layer(3, 1);
	//net << tiny_dnn::relu_layer();
	//commented out lines are not needed because of net.load
	net.load("../NeuralNetworks/partition3");


	//test case 1
	//tiny_dnn::vec_t case1 = { 0.0, 3.0, 5.0 };
	//tiny_dnn::vec_t case2 = { 2.0, 4.0, 6.0 };
	//tiny_dnn::vec_t case3 = { 5.0, 10.0, 15.0 };
	//tiny_dnn::vec_t case4 = { 12.0, 13.0, 14.0 };

	/*
	std::cout << "Real value: " << partition3[0][3][5];
	std::cout << std::endl;
	std::cout << "Predicted: " << net.predict(case1)[0];
	std::cout << std::endl;

	std::cout << "Real value: " << partition3[2][4][6];
	std::cout << std::endl;
	std::cout << "Predicted: " << net.predict(case2)[0];
	std::cout << std::endl;

	std::cout << "Real value: " << partition3[5][10][15];
	std::cout << std::endl;
	std::cout << "Predicted: " << net.predict(case3)[0];
	std::cout << std::endl;

	std::cout << "Real value: " << partition3[12][13][14];
	std::cout << std::endl;
	std::cout << "Predicted: " << net.predict(case4)[0];
	std::cout << std::endl;
	*/
	



	std::vector<tiny_dnn::vec_t> X;
	std::vector<tiny_dnn::vec_t> result;

	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				if (partition3[i1][i2][i3] != 120)
				{
					tiny_dnn::vec_t vx = { float(i1), float(i2), float(i3) };
					X.push_back(vx);
					tiny_dnn::vec_t vy = { float(partition3[i1][i2][i3]) };
					result.push_back(vy);
				}
			}
		}
	}

	size_t batch_size = 10;
	int epochs = 100;
	tiny_dnn::adamax opt;

	int iEpoch = 0;
	auto on_enumerate_epoch = [&]() {
		// compute loss and disp 1/100 of the time
		iEpoch++;
		//if (iEpoch % 1) return;

		double loss = net.get_loss<tiny_dnn::mse>(X, result);
		std::cout << "epoch=" << iEpoch << "/" << epochs << " loss=" << loss
			<< std::endl;
	};

	std::cout << "learning partition 3 with 2000 epochs:" << std::endl;
	net.fit<tiny_dnn::mse>(opt, X, result, batch_size, epochs, []() {}, on_enumerate_epoch);

	net.save("../NeuralNetworks/partition3");
}


void pick_out_elements(int****** partition, std::vector<tiny_dnn::vec_t>& X, std::vector<tiny_dnn::vec_t>& result, int number_of_elements, int skip_between, int first_index_start)
{
	int temp[96];
	for (int i = 0; i < 96; i++)
	{
		temp[i] = 0;
	}
	int elements_grabbed = 0;
	int skip_counter = 0;
	for (int i1 = first_index_start; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				for (int i4 = 0; i4 < 16; i4++)
				{
					for (int i5 = 0; i5 < 16; i5++)
					{
						for (int i6 = 0; i6 < 16; i6++)
						{
							if (partition[i1][i2][i3][i4][i5][i6] != 120)
							{

								
								if (skip_counter >= skip_between)
								{
									skip_counter = 0;
									temp[i1] = 1;
									temp[i2 + 16] = 1;
									temp[i3 + 32] = 1;
									temp[i4 + 48] = 1;
									temp[i5 + 64] = 1;
									temp[i6 + 80] = 1;

									tiny_dnn::vec_t vx;
									for (int i = 0; i < 96; i++)
									{
										vx.push_back(temp[i]);
									}

									X.push_back(vx);

									temp[i1] = 0;
									temp[i2 + 16] = 0;
									temp[i3 + 32] = 0;
									temp[i4 + 48] = 0;
									temp[i5 + 64] = 0;
									temp[i6 + 80] = 0;

									tiny_dnn::vec_t vy = { float(partition[i1][i2][i3][i4][i5][i6]) };
									result.push_back(vy);
									elements_grabbed++;
									if (elements_grabbed >= number_of_elements)
									{
										return;
									}
								}
								else
								{
									skip_counter++;
								}
							}
						}
					}
				}
			}
		}
		std::cout << "Finished 1/16" << std::endl;
	}
}

void trainPartition1or2Encoded(int****** partition, std::string partition_name)
{
	tiny_dnn::network<tiny_dnn::sequential> net;
	//net << tiny_dnn::fully_connected_layer(96, 120);
	//net << tiny_dnn::fully_connected_layer(120, 80);
	//net << tiny_dnn::fully_connected_layer(80, 40);
	//net << tiny_dnn::fully_connected_layer(40, 16);
	//net << tiny_dnn::fully_connected_layer(16, 1);
	//net.save(partition_name + "Encoded");
	net.load(partition_name + "Encoded");

	std::vector<tiny_dnn::vec_t> X;
	std::vector<tiny_dnn::vec_t> result;

	pick_out_elements(partition, X, result, 400, 890, 1);
	pick_out_elements(partition, X, result, 400, 890, 3);
	pick_out_elements(partition, X, result, 400, 890, 5);
	pick_out_elements(partition, X, result, 400, 890, 7);
	pick_out_elements(partition, X, result, 400, 890, 9);
	pick_out_elements(partition, X, result, 400, 890, 11);
	pick_out_elements(partition, X, result, 400, 890, 13);
	pick_out_elements(partition, X, result, 400, 890, 15);
	//pick_out_elements(partition, X, result, 400, 110, 14);

	std::cout<< "Size of X: " << X.size() << std::endl;

	size_t batch_size = 30;
	int epochs = 10;
	tiny_dnn::adamax opt;


	double current_lowwest_loss;

	std::cout << "Going for first loss calculation" << std::endl;
	current_lowwest_loss = net.get_loss<tiny_dnn::mse>(X, result);
	std::cout << "Starting with loss of: " << current_lowwest_loss;

	int iEpoch = 0;
	auto on_enumerate_epoch = [&]() {
		// compute loss and disp 1/100 of the time
		iEpoch++;
		//if (iEpoch % 1) return;
		double loss = net.get_loss<tiny_dnn::mse>(X, result);
		if (loss < current_lowwest_loss)
		{
			net.save(partition_name + "Encoded");
			current_lowwest_loss = loss;
		}
		else if (loss - current_lowwest_loss > 10000)
		{
			std::cout << "Changing back to previous best version" << std::endl;
			std::cout << "Attempted loss was: " << loss << std::endl;
			net.load(partition_name + "Encoded");
			loss = current_lowwest_loss;

		}
		if (loss < 2900)
		{
			opt.alpha = 0.001;
		}
		else
		{
			opt.alpha = 0.002;
		}
		std::cout << "epoch=" << iEpoch << "/" << epochs << " loss=" << loss
			<< std::endl;
	};

	std::cout << "Learning partition of size 6:" << std::endl;
	net.fit<tiny_dnn::mse>(opt, X, result, batch_size, epochs, []() {}, on_enumerate_epoch);



	double loss = net.get_loss<tiny_dnn::mse>(X, result);
	if (loss < current_lowwest_loss)
	{
		net.save(partition_name + "Encoded");
	}
}




void trainPartition3Encoded(int*** partition3)
{
	tiny_dnn::network<tiny_dnn::sequential> net;
	//net << tiny_dnn::fully_connected_layer(48, 96);
	//net << tiny_dnn::fully_connected_layer(96, 48);
	//net << tiny_dnn::fully_connected_layer(48, 16);
	//net << tiny_dnn::fully_connected_layer(16, 1);
	net.load("../NeuralNetworks/partition3Encoded");

	std::vector<tiny_dnn::vec_t> X;
	std::vector<tiny_dnn::vec_t> result;

	int temp[48];
	for (int i = 0; i < 48; i++)
	{
		temp[i] = 0;
	}

	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				if (partition3[i1][i2][i3] != 120)
				{
					temp[i1] = 1;
					temp[i2 + 16] = 1;
					temp[i3 + 32] = 1;
					
					tiny_dnn::vec_t vx;
					for (int i = 0; i < 48; i++)
					{
						vx.push_back(temp[i]);
					}

					X.push_back(vx);

					temp[i1] = 0;
					temp[i2 + 16] = 0;
					temp[i3 + 32] = 0;

					tiny_dnn::vec_t vy = { float(partition3[i1][i2][i3]) };

					result.push_back(vy);
				}
			}
		}
	}

	size_t batch_size = 10;
	int epochs = 10;
	tiny_dnn::adamax opt;


	double current_lowwest_loss;

	current_lowwest_loss = net.get_loss<tiny_dnn::mse>(X, result);
	std::cout << "Starting with loss of: " << current_lowwest_loss;

	int iEpoch = 0;
	auto on_enumerate_epoch = [&]() {
		// compute loss and disp 1/100 of the time
		iEpoch++;
		//if (iEpoch % 1) return;
		double loss = net.get_loss<tiny_dnn::mse>(X, result);
		if (loss < current_lowwest_loss)
		{
			net.save("../NeuralNetworks/partition3Encoded");
			current_lowwest_loss = loss;
		}
		else if (loss - current_lowwest_loss > 750)
		{
			std::cout << "Changing back to previous best version" << std::endl;
			std::cout << "Attempted loss was: " << loss << std::endl;
			net.load("../NeuralNetworks/partition3Encoded");
			loss = current_lowwest_loss;
			
		}
		if (loss < 2900)
		{
			opt.alpha = 0.001;
		}
		else
		{
			opt.alpha = 0.002;
		}
		std::cout << "epoch=" << iEpoch << "/" << epochs << " loss=" << loss
			<< std::endl;
	};

	std::cout << "learning partition 3 with 100 epochs:" << std::endl;
	net.fit<tiny_dnn::mse>(opt, X, result, batch_size, epochs, []() {}, on_enumerate_epoch);



	double loss = net.get_loss<tiny_dnn::mse>(X, result);
	if (loss < current_lowwest_loss)
	{
		net.save("../NeuralNetworks/partition3Encoded");
	}

	



}