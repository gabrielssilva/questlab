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
         * TODO readDocument()
         * used
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
         * TODO splitNgrams()
         * used
         */
        public static function splitNgrams($document)
        {
            $n = 3;
            $affix = implode(' ', array_fill(0, $n-1, ' '));
            $document = $affix.$document.$affix;
            $ngrams = array();
            for($i=0; $i<mb_strlen($document)-$n; $i++) {
                $ngrams[] = mb_substr($document, $i, $n);
            }


            return $ngrams;
        }


        /**
         * TODO compare()
         * used
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
         * TODO getVector()
         * used
         */
        protected static function getVector($tfs, $idf_N, $idf_n)
        {
            // TF * IDF
            $tfidfs = self::getTFIDFs($tfs, $idf_N, $idf_n);


            return $tfidfs;
        }


        /**
         * TODO getTFIDFs()
         * used
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
         * TODO cosinus()
         * sim(a, b) = (a・b) / (||a|| * ||b||)
         * used
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
         * TODO Dot product
         * a・b = summation{i=1,n}(a[i] * b[i])
         * used
         */
        protected static function dotProduct(array $a, array $b)
        {
            $dotProduct = 0;
            $keysA = array_keys(array_filter($a));
            $keysB = array_keys(array_filter($b));
            $uniqueKeys = array_unique(array_merge($keysA, $keysB));
            foreach($uniqueKeys as $key)
            {
                if(!empty($a[$key]) && !empty($b[$key]))
                {
                    $dotProduct += ($a[$key] * $b[$key]);
                }
            }

            return $dotProduct;
        }


        /**
         * TODO Euclidean norm
         * ||x|| = sqrt(x・x) // ・ is a dot product
         * used 
         */
        protected static function norm(array $vector)
        {
            return sqrt(self::dotProduct($vector, $vector));
        }

    }

?>
