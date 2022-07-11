cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET euclidean_vector_test_constructor
   FILENAME "euclidean_vector_test_constructor.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET euclidean_vector_test_operators
   FILENAME "euclidean_vector_test_operators.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET euclidean_vector_test_friends
   FILENAME "euclidean_vector_test_friends.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET euclidean_vector_test_member_functions
   FILENAME "euclidean_vector_test_member_functions.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET euclidean_vector_test_utility
   FILENAME "euclidean_vector_test_utility.cpp"
   LINK euclidean_vector
)