<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\agents\toplevel;


    /**
     * Agent to display a HTML-page.
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class HtmlAgent extends \hhu\z\agents\ToplevelAgent
    {




        /**
         * Construct a new HtmlAgent.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         * @param   \nre\core\Logger    $log        Logger instance
         */
        protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
        {
            parent::__construct($request, $response, $log);


            $this->setLanguage($request);
        }


        /**
         * Action: index.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function index(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add menu
            $this->addSubAgent('Menu');

            // Add Seminary sidebar
            $this->addSubAgent('Seminarybar');
        }




        /**
         * Set requested language.
         * 
         * @param   \nre\core\Request   $request    Current request
         */
        private function setLanguage(\nre\core\Request $request)
        {
            // Set domain
            $domain = \nre\configs\AppConfig::$app['genericname'];

            // Get language
            $locale = $this->determineLanguage($request);

            // Set Locale and Load translation
            if(!is_null($locale))
            {
                putenv("LC_ALL=$locale");
                setlocale(LC_ALL, $locale);
                \Locale::setDefault($locale);

                bindtextdomain($domain, ROOT.DS.\nre\configs\AppConfig::$dirs['locale']);
                textdomain($domain);
            }
        }


        /**
         * Determine which language is either requested directly or by browser
         * setting.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @return  string                          Requested language or default one
         */
        private function determineLanguage(\nre\core\Request $request)
        {
            // Get supported languages
            $supportedLanguages = \nre\configs\AppConfig::$app['languages'];
            if(empty($supportedLanguages)) {
                return null;
            }

            // Get requested language
            $language = $request->getGetParam('lang', 'language');
            if(!is_null($language) && array_key_exists($language, $supportedLanguages)) {
                return $supportedLanguages[$language];
            }

            // Negotiate language
            return $this->negotiateLanguage($supportedLanguages, $request->getBrowserLanguages());
        }


        /**
         * Negotiate which language the browser wants most out of the supported
         * languages.
         * 
         * @param   array   $supportedLanguages List of supported languages
         * @param   array   $browserLanguages   List of browser languages
         * @return  string                      Negotiated language or default one
         */
        private function negotiateLanguage($supportedLanguages, $browserLanguages)
        {
            if(!is_null($browserLanguages))
            {
                // Create array with languages and their ratings
                $parsedLanguages = array();
                $languages = explode(',', $browserLanguages);
                foreach($languages as &$language)
                {
                    if(($pos = strpos($language, ';q=')) !== false) {
                        $parsedLanguages[substr($language, 1, min(2, $pos-1))] = floatval(substr($language, $pos+3));
                    }
                    else {
                        $parsedLanguages[$language] = 1.0;
                    }
                }

                // Sort languages by their ratings
                arsort($parsedLanguages);

                // Get highest supported language
                foreach($parsedLanguages as $language => $rating) {
                    if(array_key_exists($language, $supportedLanguages)) {
                        return $supportedLanguages[$language];
                    }
                }
            }


            // Return default language
            return $supportedLanguages[array_keys($supportedLanguages)[0]];
        }

    }

?>
