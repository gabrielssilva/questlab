<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\requests;


    /**
     * Representation of a web-request.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class WebRequest extends \nre\core\Request
    {
        /**
         * Passed GET-parameters
         * 
         * @var array
         */
        private $getParams = array();
        /**
         * Passed POST-parameters
         * 
         * @var array
         */
        private $postParams = array();
        /**
         * Stored routes
         * 
         * @var array
         */
        private $routes = array();
        /**
         * Stored reverse-routes
         * 
         * @var array
         */
        private $reverseRoutes = array();




        /**
         * Construct a new web-request.
         */
        public function __construct()
        {
            // Detect current request
            $this->detectRequest();

            // Load GET-parameters
            $this->loadGetParams();

            // Load POST-parameters
            $this->loadPostParams();

            // Detect AJAX
            $this->detectAJAX();
        }




        /**
         * Get a parameter.
         * 
         * @param   int     $index          Index of parameter
         * @param   string  $defaultIndex   Index of default configuration value for this parameter
         * @return  string                  Value of parameter
         */
        public function getParam($index, $defaultIndex=null)
        {
            if($index == 0) {
                return $this->getGetParam('layout', $defaultIndex);
            }
            else {
                return parent::getParam($index-1, $defaultIndex);
            }
        }


        /**
         * Get all parameters from index on.
         * 
         * @param   int     $offset Offset-index
         * @return  array           Parameters
         */
        public function getParams($offset=0)
        {
            if($offset == 0)
            {
                return array_merge(
                    array(
                        $this->getGetParam('layout', 'toplevel')
                    ),
                    parent::getParams()
                );
            }


            return array_slice($this->params, $offset-1);
        }


        /**
         * Get a GET-parameter.
         * 
         * @param   string  $key            Key of GET-parameter
         * @param   string  $defaultIndex   Index of default configuration value for this parameter
         * @return  string                  Value of GET-parameter
         */
        public function getGetParam($key, $defaultIndex=null)
        {
            // Check key
            if(array_key_exists($key, $this->getParams))
            {
                // Return value
                return $this->getParams[$key];
            }


            // Return default value
            return \nre\core\Config::getDefault($defaultIndex);
        }


        /**
         * Get all GET-parameters.
         * 
         * @return  array   GET-Parameters
         */
        public function getGetParams()
        {
            return $this->getParams;
        }


        /**
         * Get a POST-parameter.
         * 
         * @param   string  $key            Key of POST-parameter
         * @param   string  $defaultValue   Default value for this parameter
         * @return  string                  Value of POST-parameter
         */
        public function getPostParam($key, $defaultValue=null)
        {
            // Check key
            if(array_key_exists($key, $this->postParams))
            {
                // Return value
                return $this->postParams[$key];
            }


            // Return default value
            return $defaultValue;
        }


        /**
         * Get all POST-parameters.
         * 
         * @return  array   POST-parameters
         */
        public function getPostParams()
        {
            return $this->postParams;
        }


        /**
         * Get the method of the current request.
         * 
         * @return  string  Current request method
         */
        public function getRequestMethod()
        {
            return $_SERVER['REQUEST_METHOD'];
        }


        /**
         * Add a URL-route.
         * 
         * @param   string  $pattern        Regex-Pattern that defines the routing
         * @param   string  $replacement    Regex-Pattern for replacement
         * @param   bool    $isLast         Stop after that rule
         */
        public function addRoute($pattern, $replacement, $isLast=false)
        {
            // Store route
            $this->routes[] = $this->newRoute($pattern, $replacement, $isLast);
        }


        /**
         * Add a reverse URL-route.
         * 
         * @param   string  $pattern        Regex-Pattern that defines the reverse routing
         * @param   string  $replacement    Regex-Pattern for replacement
         * @param   bool    $isLast         Stop after that rule
         */
        public function addReverseRoute($pattern, $replacement, $isLast=false)
        {
            // Store reverse route
            $this->reverseRoutes[] = $this->newRoute($pattern, $replacement, $isLast);
        }


        /**
         * Apply stored reverse-routes to an URL
         * 
         * @param   string  $url    URL to apply reverse-routes to
         * @return  string          Reverse-routed URL
         */
        public function applyReverseRoutes($url)
        {
            return $this->applyRoutes($url, $this->reverseRoutes);
        }


        /**
         * Revalidate the current request
         */
        public function revalidate()
        {
            $this->detectRequest();
        }


        /**
         * Get a SERVER-parameter.
         * 
         * @param   string  $key    Key of SERVER-parameter
         * @return  string          Value of SERVER-parameter
         */
        public function getServerParam($key)
        {
            if(array_key_exists($key, $_SERVER)) {
                return $_SERVER[$key];
            }


            return null;
        }




        /**
         * Detect the current HTTP-request.
         */
        private function detectRequest()
        {
            // URL ermitteln
            $url = isset($_GET) && array_key_exists('url', $_GET) ? $_GET['url'] : '';
            $url = trim($url, '/');

            // Routes anwenden
            $url = $this->applyRoutes($url, $this->routes);

            // URL splitten
            $params = explode('/', $url);
            if(empty($params[0])) {
                $params = array();
            }


            // Parameter speichern
            $this->params = $params;
        }


        /**
         * Determine parameters passed by GET.
         */
        private function loadGetParams()
        {
            if(isset($_GET)) {
                $this->getParams = $_GET;
            }
        }


        /**
         * Determine parameters passed by POST.
         */
        private function loadPostParams()
        {
            if(isset($_POST)) {
                $this->postParams = $_POST;
            }
        }


        /**
         * Detect an AJAX-request by checking the X-Requested-With
         * header and set the layout to 'ajax' in this case.
         */
        private function detectAjax()
        {
            // Get request headers
            $headers = apache_request_headers();

            // Check X-Requested-With header and set layout
            if(array_key_exists('X-Requested-With', $headers) && $headers['X-Requested-With'] == 'XMLHttpRequest') {
                if(!array_key_exists('layout', $this->getParams)) {
                    $this->getParams['layout'] = 'ajax';
                }
            }
        }


        /**
         * Create a new URL-route.
         * 
         * @param   string  $pattern        Regex-Pattern that defines the reverse routing
         * @param   string  $replacement    Regex-Pattern for replacement
         * @param   bool    $isLast         Stop after that rule
         * @return  array                   New URL-route
         */
        private function newRoute($pattern, $replacement, $isLast=false)
        {
            return array(
                'pattern'    =>    $pattern,
                'replacement'    =>    $replacement,
                'isLast'    =>    $isLast
            );
        }


        /**
         * Apply given routes to an URL
         * 
         * @param   string  $url    URL to apply routes to
         * @param   array   $routes Routes to apply
         * @return  string          Routed URL
         */
        private function applyRoutes($url, $routes)
        {
            // Traverse given routes
            foreach($routes as &$route)
            {
                // Create and apply Regex
                $urlR = preg_replace(
                    '>'.$route['pattern'].'>i',
                    $route['replacement'],
                    $url
                );

                // Split URL
                $get = '';
                if(($gpos = strrpos($urlR, '?')) !== false) {
                    $get = substr($urlR, $gpos+1);
                    $urlR = substr($urlR, 0, $gpos);
                }

                // Has current route changed anything?
                if($urlR != $url || !empty($get))
                {
                    // Extract GET-parameters
                    if(strlen($get) > 0)
                    {
                        $gets = explode('&', $get);
                        foreach($gets as $get)
                        {
                            $get = explode('=', $get);
                            if(!array_key_exists($get[0], $this->getParams)) {
                                $this->getParams[$get[0]] = $get[1];
                            }
                        }
                    }


                    // Stop when route “isLast”
                    if($route['isLast']) {
                        $url = $urlR;
                        break;
                    }
                }


                // Set new URL
                $url = $urlR;
            }


            // Return routed URL
            return $url;
        }

    }

?>
