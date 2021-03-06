<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\drivers;


    /**
     * Implementation of a database driver for MySQL-databases.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class MysqliDriver extends \nre\drivers\DatabaseDriver
    {




        /**
         * Construct a MySQL-driver.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @param   array   $config Connection and login settings
         */
        function __construct($config)
        {
            parent::__construct($config);
        }




        /**
         * Execute a SQL-query.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @param   string  $query  Query to run
         * @param   mixed   …       Params
         * @return  array           Result
         */
        public function query($query)
        {
            // Prepare statement
            if(!($stmt = $this->connection->prepare($query))) {
                throw new \nre\exceptions\DatamodelException($this->connection->error, $this->connection->errno);
            }

            try {
                // Prepare data
                $data = array();

                // Bind parameters
                $p = array_slice(func_get_args(), 1);
                $params = array();
                foreach($p as $key => $value) {
                    $params[$key] = &$p[$key];
                }
                if(count($params) > 0)
                {
                    if(!(call_user_func_array(array($stmt, 'bind_param'), $params))) {
                        throw new \nre\exceptions\DatamodelException($this->connection->error, $this->connection->errno);
                    }
                }

                // Execute query
                if(!$stmt->execute()) {
                    throw new \nre\exceptions\DatamodelException($this->connection->error, $this->connection->errno);
                }

                // Fetch result
                if($result = $stmt->get_result()) {
                    while($row = $result->fetch_assoc()) {
                        $data[] = $row;
                    }
                }


                $stmt->close();
                return $data;
            }
            catch(\Exception $e) {
                $stmt->close();
                throw $e;
            }
        }


        /**
         * Return the last insert id (of the last insert-query).
         * 
         * @return  int Last insert id
         */
        public function getInsertId()
        {
            return $this->connection->insert_id;
        }


        /**
         * Enable/disable autocommit feature.
         * 
         * @param   boolean $autocommit Enable/disable autocommit
         */
        public function setAutocommit($autocommit)
        {
            $this->connection->autocommit($autocommit);
        }


        /**
         * Rollback the current transaction.
         */
        public function rollback()
        {
            $this->connection->rollback();
        }


        /**
         * Commit the current transaction.
         */
        public function commit()
        {
            $this->connection->commit();
        }




        /**
         * Establish a connect to a MqSQL-database.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @param   array   $config Connection and login settings
         */
        protected function connect($config)
        {
            // Connect
            $con = @new \mysqli(
                $config['host'],
                $config['user'],
                $config['password'],
                $config['db']
            );

            // Check connection
            if($con->connect_error) {
                throw new \nre\exceptions\DatamodelException($con->connect_error, $con->connect_errno);
            }

            // Set character encoding
            if(!$con->set_charset('utf8mb4')) {
                throw new \nre\exceptions\DatamodelException($con->connect_error, $con->connect_errno);
            }

            // Save connection
            $this->connection = $con;
        }

    }

?>
