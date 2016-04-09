<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\lib;


    /**
     * Class to calculate similarity between documents.
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class Similarity
    {


        /**
         * Read a file and return its text.
         *
         * Currently only PDF-files are supported and “pdftotext” needs to be
         * installed. If reading fails, false is returned.
         *
         * @param   string  $filename   Name of file to read
         * @return  mixed               Text of document (string) or false (boolean)
         */
        public static function readDocument($filename)
        {
            if(!file_exists($filename)) {
                return false;
            }

            $text = array();
            $result = 0;
            exec(sprintf('pdftotext "%s" -', $filename), $text, $result);
            if($result != 0) {
                return false;
            }

            $text = mb_strtolower(implode('', $text));


            return $text;
        }


        /**
         * Split a text into N-grams.
         *
         * The default N is 3.
         *
         * @param   string  $document   Text to be splitted
         * @param   int     $n          Size of grams to split into (N)
         * @return  array               List of n-grams
         */
        public static function splitNgrams($document, $n=3)
        {
            $affix = implode(' ', array_fill(0, $n-1, ' '));
            $document = $affix.$document.$affix;
            $ngrams = array();
            for($i=0; $i<mb_strlen($document)-$n; $i++) {
                $ngrams[] = mb_substr($document, $i, $n);
            }


            return $ngrams;
        }


        /**
         * Compare to documents, represented by there Term Frequencies (TFs)
         * values.
         *
         * $tfsA, $tfsB and $idf_n are expected to be associative arrays with
         * the term as key and the corresponding frequency as value.
         *
         * @param   array   $tfsA   Term Frequencies of document A
         * @param   array   $tfsB   Term Frequencies of document B
         * @param   int     $idf_N  Total count of documents in corpus
         * @param   array   $idf_n  Inverse Document Frequencies of all terms
         * @return  float           Similarity value (between 0.0 and 1.0)
         */
        public static function compare($tfsA, $tfsB, $idf_N, $idf_n)
        {
            // Create vector A
            $vectorA = self::getVector($tfsA, $idf_N, $idf_n);

            // Create vector B
            $vectorB = self::getVector($tfsB, $idf_N, $idf_n);

            // Compare vectors
            $result = self::cosinus($vectorA, $vectorB);


            // Return result
            return $result;
        }




        /**
         * Calculate the vector for a document based on TF and IDF.
         *
         * $tfs and $idf_n are expected to be associative arrays with the term
         * as key and the corresponding frequency as value. The resulting
         * vector is an associative array with the terms as keys and their
         * corresponding values as value.
         *
         * @param   array   $tfs    Term Frequencies of document
         * @param   int     $idf_N  Total count of documents in corpus
         * @param   array   $idf_n  Inverse Document Frequencies of all terms
         * @return  array           Document vector
         */
        protected static function getVector($tfs, $idf_N, $idf_n)
        {
            // TF * IDF
            $tfidfs = self::getTFIDFs($tfs, $idf_N, $idf_n);


            return $tfidfs;
        }


        /*
         * Calculate TF*IDF values for a document.
         *
         * $tfs and $idf_n are expected to be associative arrays with the term
         * as key and the corresponding frequency as value. The resulting
         * value is an associative array with the terms as keys and their
         * corresponding TF*IDF as values.
         *
         * @param   array   $tfs    Term Frequencies of document
         * @param   int     $idf_N  Total count of documents in corpus
         * @param   array   $idf_n  Inverse Document Frequencies of all terms
         * @return  array           TF*IDF values
         */
        protected static function getTFIDFs($tfs, $idf_N, $idf_n)
        {
            $tfidfs = array();

            // Calculate TF*IDF
            foreach($tfs as $term => &$tf)
            {
                if(array_key_exists($term, $idf_n)) {
                    $idf = log($idf_N / $idf_n[$term], 2);
                }
                else {
                    // TODO Laplace norm: n = 1?
                    $idf = log($idf_N / 1, 2);
                }
                $tfidfs[$term] = $tf * $idf;
            }


            return $tfidfs;
        }


        /**
         * Calculate cosinus similarity between two vectors.
         *
         * sim(a, b) = (a・b) / (||a|| * ||b||)
         *
         * @param   array   $a  Vector A
         * @param   array   $b  Vector B
         * @return  float       Similarity value (between 0.0 and 1.0)
         */
        protected static function cosinus(array $a, array $b)
        {
            $normA = self::norm($a);
            $normB = self::norm($b);
            if(($normA * $normB) != 0) {
                return self::dotProduct($a, $b) / ($normA * $normB);
            }
            else {
                return 0;
            }
        }


        /**
         * Calculate the dot-product for two vectors.
         * 
         * a・b = summation{i=1,n}(a[i] * b[i])
         *
         * @param   array   $a  Vector A
         * @param   array   $b  Vector B
         * @return  float       Dot-product
         */
        protected static function dotProduct(array $a, array $b)
        {
            $dotProduct = 0;
            $keysA = array_keys(array_filter($a));
            $keysB = array_keys(array_filter($b));
            $uniqueKeys = array_unique(array_merge($keysA, $keysB));
            foreach($uniqueKeys as $key) {
                if(!empty($a[$key]) && !empty($b[$key])) {
                    $dotProduct += ($a[$key] * $b[$key]);
                }
            }

            return $dotProduct;
        }


        /**
         * Caculate the Euclidean norm for a vector.
         *
         * ||x|| = sqrt(x・x) // ・ is a dot product
         *
         * @param   array   $vector Vector
         * @return  float           Euclidean norm
         */
        protected static function norm(array $vector)
        {
            return sqrt(self::dotProduct($vector, $vector));
        }

    }

?>
