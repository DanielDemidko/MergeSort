#include <iostream>
#include <vector>


template<typename T> std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec)
{
    for (const auto &i : vec)
    {
        out << i << ' ';
    }
    return out;
}

template<typename T> std::vector<std::vector<T>> SplitToSortedPairs(const std::vector<T> &vec)
{
    std::vector<std::vector<T>> result;
    const auto isOdd = vec.size() % 2;
    for (int i = 0; i < (isOdd ? vec.size() - 1 : vec.size()); i += 2)
    {
        const auto &first = vec[i], sec = vec[i + 1];
        result.push_back((first < sec) ? std::vector<T>{first, sec} : std::vector<T>{sec, first});
    }
    if (isOdd)
    {
        result.push_back({ vec.back() });
    }
    return result;
}

template<typename T> std::vector<T> JoinSorted(std::vector<T> res, const std::vector<T> &second)
{
    for (const auto &j : second)
    {
        bool isAppend = false;
        for (auto i = res.begin(); i < res.end(); ++i)
        {
            if (*i >= j)
            {
                res.insert(i, j);
                isAppend = true;
                break;
            }
        }
        if (!isAppend)
        {
            res.push_back(j);
        }
    }
    return res;
}

template<typename T> std::vector<T> JoinSorted(std::vector<std::vector<T>> vec)
{
    if (vec.empty())
    {
        return {};
    }
    while (vec.size() > 1)
    {
        std::vector<std::vector<T>> buffer;
        const auto isOdd = vec.size() % 2;
        for (int i = 0; i < (isOdd ? vec.size() - 1 : vec.size()); i += 2)
        {
            buffer.push_back(JoinSorted(std::move(vec[i]), vec[i + 1]));
        }
        if (isOdd)
        {
            buffer.push_back(vec.back());
        }
        vec = std::move(buffer);
    }
    return vec.front();
}

template<typename T> std::vector<T> MergeSort(const std::vector<T> &vec)
{
    return JoinSorted(SplitToSortedPairs(vec));
}

int main()
{
    std::cout << MergeSort<int>({ 9, 8, 7, 8, 6, 2, 3, 5, 1, 0, 9, 4, 3, 6, 7, 10 }) << std::endl;
}

