#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

class Sort
{
private:
	int *oriData;			// ԭʼ�������� 
	int *usiData;			// ����������������� 
	int size;				// ���ݴ�С 
	long long comparecount;	// �Ƚϴ��� 
	long long swapcount;	// �������� 
public:
	Sort(int n);
	~Sort() { }
	void generate();
	void reset();
	void Bubble_Sort();
	void Selection_Sort();
	void Insert_Sort();
	void Shell_Sort();
	void Quick_Sort();
	void qsort(int low, int high);
	void Heap_Sort();
	void max_heapify(int start, int end);
	void Merge_Sort(); 
	void mergeSort(int left, int right); 
	void merge(int left, int mid, int right);
	void Radix_Sort();
	void ModeSelect();
};

Sort::Sort(int n)
{
	oriData = new int[n];
	usiData = new int[n];
	size = n;
	comparecount = 0;
	swapcount = 0;
}

void Sort::generate()
{
	srand(static_cast<unsigned>(time(NULL)));
	for(int i = 0; i < size; i++)
	{
		oriData[i] = usiData[i] = rand();
	}
}

void Sort::reset()
{
	for(int i = 0; i < size; i++)
	{
		usiData[i] = oriData[i];
	}
	comparecount = 0;
	swapcount = 0;
}

void Sort::Bubble_Sort()
{
	clock_t start = clock();
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size - i - 1; j++)
		{
			if (usiData[j] > usiData[j+1])
			{
				swap(usiData[j], usiData[j+1]);
				swapcount++;
			}
			comparecount++;
		}
	}
	clock_t end = clock();
	double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "ð����������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "ð�����򽻻�������" << "\t" << swapcount << endl;
	cout << "ð������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}

void Sort::Selection_Sort()
{
	clock_t start = clock();
	int min;
	for(int i = 0; i < size - 1; i++)
	{
		min = i;
		for(int j = i + 1; j < size; j++)
		{
			if (usiData[j] < usiData[min])
				min = j;
			comparecount++;
		}
		swap(usiData[i], usiData[min]);
		swapcount++;
	}
	clock_t end = clock();
	double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "ѡ����������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "ѡ�����򽻻�������" << "\t" << swapcount << endl;
	cout << "ѡ������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}

void Sort::Insert_Sort()
{
	clock_t start = clock();
	int i = 0, j = 0; 
	for(i = 1; i < size; i++)
	{
		if(usiData[i] < usiData[i-1])
		{
			int temp = usiData[i];
			for(j = i-1; j >= 0 && usiData[j] > temp; j--)
			{
				usiData[j+1] = usiData[j];
				comparecount++;
			}
			usiData[j+1] = temp;
			swapcount++;
		}
		comparecount++;
	}
	clock_t end = clock();
	double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "ֱ�Ӳ�����������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "ֱ�Ӳ������򽻻�������" << "\t" << swapcount << endl;
	cout << "ֱ�Ӳ�������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}

void Sort::Shell_Sort()
{
	clock_t start = clock();
	int i = 0, j = 0;
	for(int gap = size / 2; gap > 0; gap = int(gap / 2.2))
	{
		for(i = gap; i < size; i++)
		{
			if(usiData[i] < usiData[i-gap])
			{
				int temp = usiData[i];
				for(j = i-gap; j >= 0 && usiData[j] > temp; j -= gap)
				{
					usiData[j + gap] = usiData[j];
					comparecount++;
				}
				usiData[j + gap] = temp;
				swapcount++;
			}
			comparecount++;
		}
	}
	clock_t end = clock();
	double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "ϣ����������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "ϣ�����򽻻�������" << "\t" << swapcount << endl;
	cout << "ϣ������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}

void Sort::Quick_Sort()
{
	clock_t start = clock();
	qsort(0, size-1);
	clock_t end = clock();
	double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "������������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "�������򽻻�������" << "\t" << swapcount << endl;
	cout << "��������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}
void Sort::qsort(int low, int high)
{
	if(high <= low)
		return;
	int i = low, j = high;
	int key = usiData[low];
	while(true)
	{
		while (usiData[i] <= key)
		{
			comparecount++;
			i++;
			if(i == high)
				break;
		}
		comparecount++;
		while (usiData[j] >= key)
		{
			comparecount++;
			j--;
			if(j == low)
				break;
		}
		comparecount++;
		if (i >= j)
			break;
		swap(usiData[i], usiData[j]);
		swapcount++;
	}
	usiData[low] = usiData[j];
	usiData[j] = key;
	swapcount++;
	qsort(low, j - 1);
	qsort(j + 1, high);
}

void Sort::Heap_Sort()
{
	clock_t start = clock();
	for (int i = size / 2 - 1; i >= 0; i--)
        max_heapify(i, size - 1);
    for (int i = size - 1; i > 0; i--)
    {
        swap(usiData[0], usiData[i]);
        swapcount++;
        max_heapify(0, i - 1);
    }
    clock_t end = clock();
    double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "����������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "�����򽻻�������" << "\t" << swapcount << endl;
	cout << "������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}
void Sort::max_heapify(int start, int end)
{
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end)
    {    
        if (son + 1 <= end && usiData[son] < usiData[son + 1])
            son++;
        comparecount++;
        if (usiData[dad] > usiData[son])
        {
        	comparecount++;
            return;
		}
        else
        {
            swap(usiData[dad], usiData[son]);
            swapcount++;
            dad = son;
            son = dad * 2 + 1;
        }
		comparecount++;
    }
}

void Sort::Merge_Sort()
{
	clock_t start = clock();
	mergeSort(0, size - 1);
	clock_t end = clock();
    double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "�鲢��������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "�鲢����Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}
void Sort::mergeSort(int left, int right)
{
	if(left < right)
	{
		int mid = left + ( right - left ) / 2;
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		merge(left, mid, right);
	}
}
void Sort::merge(int left, int mid, int right)
{
	int *tempData = new int[right - left + 1];
	int i = left, j = mid + 1, k = 0;
	while(i != mid + 1 && j != right + 1)
	{
		comparecount++;
		if (usiData[i] > usiData[j])
			tempData[k++] = usiData[j++];
		else
			tempData[k++] = usiData[i++]; 
	}
	while(i != mid + 1)
		tempData[k++] = usiData[i++];
	while(j != right + 1)
		tempData[k++] = usiData[j++];
	for(i = left; i <= right; i++)
		usiData[i] = tempData[i - left];
	delete[] tempData;
}

void Sort::Radix_Sort()
{
	clock_t start = clock();
	int d = 1;
	int  p = 10;
	for(int i = 0; i < size; i++)
	{
		while(usiData[i] > p)
		{
			p *= 10;
			d++;
		}
	}
	int *tmp = new int [size];
	int *count = new int [10];
	int i, j, k;
	int radix = 1;
	for(i = 1; i <= d; i++)
	{
		for(j = 0; j < 10; j++)
			count[j] = 0;
		for(j = 0; j < size; j++)
		{
			k = (usiData[j] / radix) % 10;
			count[k]++;
		}
		for(j = 1; j < 10; j++)
			count[j] = count[j-1] + count[j];
		for(j = size - 1; j >= 0; j--)
		{
			k = (usiData[j] / radix) % 10;
			tmp[count[k] - 1] = usiData[j];
			count[k]--;
		}
		for(j = 0; j < size; j++)
			usiData[j] = tmp[j];
		radix *= 10;
	}
	delete []tmp;
	delete []count;
	
	clock_t end = clock();
	double duration = double((end - start)) / CLOCKS_PER_SEC * 1000;
	cout << "������������ʱ�䣺" << "\t" << duration << " ms" << endl;
	cout << "��������Ƚϴ�����" << "\t" << comparecount << endl;
	cout << endl ;
}

void Sort::ModeSelect()
{
	int mode = 0;
	do
	{
		while (true)
		{
	        cout << "��ѡ����Ҫ���еĲ�����";
	        cin >> mode;
	        if (cin.fail() || mode < 1 || mode > 9)
			{
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	            cout << "����������������룡" << endl;
	        }
			else
			{
	            break;
	        }
	    }
	    
	    switch (mode)
		{
			case 1:
				this->Bubble_Sort();
				break;
			case 2:
				this->Selection_Sort();
				break;
			case 3:
				this->Insert_Sort();
				break;
			case 4:
				this->Shell_Sort();
				break;
			case 5:
				this->Quick_Sort();
				break; 
			case 6:
				this->Heap_Sort();
				break;
			case 7:
				this->Merge_Sort();
				break;
			case 8:
				this->Radix_Sort();
				break;
            case 9:
                break;
            default:
                break;
        }
        
        this->reset();
        
	}while(mode != 9);
}

int main()
{
	int n;
    cout << "**                  �����㷨�Ƚ�                      **" << endl
    	 << "========================================================" << endl
    	 << "**                  1 --- ð������                    **" << endl
    	 << "**                  2 --- ѡ������                    **" << endl
    	 << "**                  3 --- ֱ�Ӳ�������                **" << endl
    	 << "**                  4 --- ϣ������                    **" << endl
    	 << "**                  5 --- ��������                    **" << endl
    	 << "**                  6 --- ������                      **" << endl
    	 << "**                  7 --- �鲢����                    **" << endl
    	 << "**                  8 --- ��������                    **" << endl
    	 << "**                  9 --- �˳�����                    **" << endl
    	 << "========================================================" << endl << endl; 
    
	cout << "������Ҫ������������ĸ�����" ;
    cin >> n;
    cout << endl;
    Sort S(n);
    S.generate();
    S.ModeSelect();
    system("pause");
	return 0;
}
