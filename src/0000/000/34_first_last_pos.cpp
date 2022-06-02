int lower_bound(const vector<int>& A, int tgt) {
	int lo = 0;
	int hi = size(A)-1;
	int lastFound = -1;
	while(lo <= hi) {
		auto mid = lo + (hi-lo)/2;
		if(A[mid]==tgt) {
			lastFound = mid;
			hi=mid-1; // look left for first occurrence
		} else if (A[mid] < tgt) {
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return lastFound;
}

int upper_bound(const vector<int>& A, int tgt) {
	int lo = 0;
	int hi = size(A)-1;
	int lastFound = -1;
	while(lo <= hi) {
		auto mid = lo + (hi-lo)/2;
		if(A[mid]==tgt) {
			lastFound = mid;
			lo=mid+1; // look right for last occurrence
		} else if (A[mid] < tgt) {
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return lastFound;
}


vector<int> searchForRange(vector<int> A, int tgt) {
	auto lb = lower_bound(A, tgt);
	auto ub = upper_bound(A, tgt);
	return {lb, ub};
}
