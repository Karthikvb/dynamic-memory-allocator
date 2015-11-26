static void do_block (int lda, int M, int N, int K, double* A, double* B, double* C) {
    int index = (M/8) * 8;

    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < K; ++k) {  

            //double bkj = B[k+j*lda];
            __m128d b = _mm_load1_pd(B+k+j*lda);

            for (int i = 0; i < index; i+=8) {
                __m128d a1 = _mm_loadu_pd(A+i+k*lda);
                __m128d a2 = _mm_loadu_pd(A+i+k*lda+2);
                __m128d a3 = _mm_loadu_pd(A+i+k*lda+4);
                __m128d a4 = _mm_loadu_pd(A+i+k*lda+6);

                __m128d c1 = _mm_loadu_pd(C+i+j*lda);
                __m128d c2 = _mm_loadu_pd(C+i+j*lda+2);
                __m128d c3 = _mm_loadu_pd(C+i+j*lda+4);
                __m128d c4 = _mm_loadu_pd(C+i+j*lda+6);

                __m128d p1 = _mm_mul_pd(a1, b);
                __m128d p2 = _mm_mul_pd(a2, b);
                __m128d p3 = _mm_mul_pd(a3, b);
                __m128d p4 = _mm_mul_pd(a4, b);

                c1 = _mm_add_pd(p1, c1);
                c2 = _mm_add_pd(p2, c2);
                c3 = _mm_add_pd(p3, c3);
                c4 = _mm_add_pd(p4, c4);

                _mm_storeu_pd(C+i+j*lda, c1);
                _mm_storeu_pd(C+i+j*lda+2, c2);
                _mm_storeu_pd(C+i+j*lda+4, c3);
                _mm_storeu_pd(C+i+j*lda+6, c4);
            }

            for (int i=index; i<M; ++i) {
                C[i+j*lda] += A[i+klda] * bkj;
            }
        }
    }
}

