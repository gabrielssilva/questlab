<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\models;


    /**
     * Model to interact with Pages-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class PagesModel extends \hhu\z\Model
    {
        /**
         * URL for system page: Introduction
         */
        const PAGEURL_INTRODUCTION = 'introduction';




        /**
         * Construct a new PagesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get all registered pages (without system pages).
         *
         * @return  array   List of registered pages
         */
        public function getPages() {
            // Get pages
            $data = $this->db->query(
                'SELECT id, pos, url, title, text '.
                'FROM pages '.
                'ORDER BY pos'
            );

            // Remove system pages
            $pages = array();
            foreach($data as $page) {
                if($page['url'] != self::PAGEURL_INTRODUCTION) {
                    $pages[] = $page;
                }
            }


            // Return pages
            return $pages;
        }


        /**
         * Get a page by its ID.
         *
         * @param   string  $pageId ID of page to get
         * @return  array           Page data
         */
        public function getPageById($pageId)
        {
            $data = $this->db->query(
                'SELECT id, url, title, pos, text '.
                'FROM pages '.
                'WHERE id = ?',
                'i',
                $pageId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get a page by its URL.
         *
         * @param   string  $pageUrl    URL of page to get
         * @return  array               Page data
         */
        public function getPageByUrl($pageUrl)
        {
            $data = $this->db->query(
                'SELECT id, url, title, pos, text '.
                'FROM pages '.
                'WHERE url = ?',
                's',
                $pageUrl
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Check if a page title already exists.
         *
         * @param   string  $title  Page title to check
         * @param   int     $pageId Do not check this ID (for editing)
         * @return  boolean         Whether title exists or not
         */
        public function titleExists($title, $pageId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM pages '.
                'WHERE title = ? OR url = ?',
                'ss',
                $title,
                self::createLinkParam($title)
            );


            return (!empty($data) && (is_null($pageId) || $pageId != $data[0]['id']));
        }


        /**
         * Create a new page.
         *
         * @param   int     $userId ID of creating user
         * @param   string  $title  Title of page to create
         * @return  int             ID of the newly created page
         */
        public function createPage($userId, $title)
        {
            // Create content
            $this->db->query(
                'INSERT INTO pages '.
                '(created_user_id, pos, title, url) '.
                'SELECT ?, IFNULL(MAX(pos),0)+1, ?, ? '.
                'FROM pages',
                'iss',
                $userId,
                $title,
                self::createLinkParam($title)
            );


            return $this->db->getInsertId();
        }


        /**
         * Edit data of a page.
         *
         * @param   int     $pageId ID of page to edit
         * @param   string  $title  New page title
         * @param   string  $text   New page text
         */
        public function editPage($pageId, $title, $text)
        {
            $this->db->query(
                'UPDATE pages '.
                'SET title = ?, url = ?, text = ? '.
                'WHERE id = ?',
                'sssi',
                $title,
                self::createLinkParam($title),
                $text,
                $pageId
            );
        }


        /**
         * Delete page.
         *
         * @param   array   $page   Page to delete
         */
        public function deletePage($page)
        {
            $this->db->setAutocommit(false);
            try {
                // Delete page
                $this->db->query('DELETE FROM pages WHERE id = ?', 'i', $page['id']);

                // Correct position
                $this->db->query(
                    'UPDATE pages '.
                    'SET pos = pos-1 '.
                    'WHERE pos > ?',
                    'i',
                    $page['pos']
                );
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }
            $this->db->setAutocommit(true);
        }




        /**
         * Mask parameters to be used in an URL.
         * 
         * @param   string  $param  First parameter
         * @return  string          Masked parameters as string
         */
        private static function createLinkParam($param)
        {
            return \nre\core\Linker::createLinkParam(mb_strtolower($param));
        }

    }

?>
